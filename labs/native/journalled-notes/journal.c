/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/journalled-notes/journal.c
 * PURPOSE: Checked one-sector WAL records and deterministic recovery in C23.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "journal.h"
#include <limits.h>
#include <stddef.h>
#include <string.h>

/* The wire encoding is byte-oriented: no host struct casts, padding, native
 * endianness or pointer values become part of a durable record. */
#define RECORD_VERSION 1U
#define RECORD_HEADER_BYTES 18U

static void Write32(unsigned char *target, uint32_t value)
{
    for (unsigned i = 0U; i < 4U; ++i) target[i] = (unsigned char)(value >> (i * 8U));
}
static void Write64(unsigned char *target, uint64_t value)
{
    for (unsigned i = 0U; i < 8U; ++i) target[i] = (unsigned char)(value >> (i * 8U));
}
static uint32_t Read32(const unsigned char *source)
{
    uint32_t value = 0U;
    for (unsigned i = 0U; i < 4U; ++i) value |= (uint32_t)source[i] << (i * 8U);
    return value;
}
static uint64_t Read64(const unsigned char *source)
{
    uint64_t value = 0U;
    for (unsigned i = 0U; i < 8U; ++i) value |= (uint64_t)source[i] << (i * 8U);
    return value;
}

static uint32_t CrcUpdate(uint32_t crc, const unsigned char *bytes, size_t length)
{
    for (size_t i = 0U; i < length; ++i) {
        crc ^= (uint32_t)bytes[i];
        for (unsigned bit = 0U; bit < 8U; ++bit) {
            const uint32_t mask = 0U - (crc & 1U);
            crc = (crc >> 1U) ^ (UINT32_C(0xEDB88320) & mask);
        }
    }
    return crc;
}

static uint32_t RecordChecksum(const unsigned char record[BTB_SECTOR_BYTES], size_t textLength)
{
    uint32_t crc = UINT32_MAX;
    crc = CrcUpdate(crc, record, 14U);
    crc = CrcUpdate(crc, record + RECORD_HEADER_BYTES, textLength);
    return ~crc;
}

static void EncodeRecord(const BtbNote *note, unsigned char kind,
                         unsigned char out[BTB_SECTOR_BYTES])
{
    memset(out, 0, BTB_SECTOR_BYTES);
    out[0] = 'B'; out[1] = 'T'; out[2] = 'B'; out[3] = kind;
    out[4] = RECORD_VERSION;
    const size_t length = strlen(note->text); /* Internal validated note. */
    out[5] = (unsigned char)length;
    Write64(out + 6U, note->revision);
    memcpy(out + RECORD_HEADER_BYTES, note->text, length);
    Write32(out + 14U, RecordChecksum(out, length));
}

static BtbJournalStatus DecodeRecord(const unsigned char raw[BTB_SECTOR_BYTES],
                                     unsigned char expectedKind, BtbNote *out,
                                     int *present)
{
    /* A fresh sector is all zero. An invalid non-empty sector is NOT treated
     * as absent: doing so would silently discard possible accepted work. */
    int empty = 1;
    for (size_t i = 0U; i < BTB_SECTOR_BYTES; ++i) {
        if (raw[i] != 0U) { empty = 0; break; }
    }
    if (empty) { *present = 0; return BTB_JOURNAL_OK; }
    *present = 1;
    if (raw[0] != 'B' || raw[1] != 'T' || raw[2] != 'B' || raw[3] != expectedKind ||
        raw[4] != RECORD_VERSION || raw[5] >= BTB_NOTE_TEXT_CAPACITY) {
        return BTB_JOURNAL_CORRUPT;
    }
    const size_t length = (size_t)raw[5];
    const uint64_t revision = Read64(raw + 6U);
    if (revision == 0U || RecordChecksum(raw, length) != Read32(raw + 14U)) {
        return BTB_JOURNAL_CORRUPT;
    }
    for (size_t i = RECORD_HEADER_BYTES; i < RECORD_HEADER_BYTES + length; ++i) {
        if (raw[i] == 0U) return BTB_JOURNAL_CORRUPT; /* Canonical text, no hidden suffix. */
    }
    for (size_t i = RECORD_HEADER_BYTES + length; i < BTB_SECTOR_BYTES; ++i) {
        if (raw[i] != 0U) return BTB_JOURNAL_CORRUPT;
    }
    BtbNote result = {0};
    result.revision = revision;
    memcpy(result.text, raw + RECORD_HEADER_BYTES, length);
    result.text[length] = '\0';
    *out = result;
    return BTB_JOURNAL_OK;
}

/* Two independently encoded records provide visible post-crash evidence.
 * An invalid journal is not ignored even when the snapshot looks valid. */
static BtbJournalStatus ReadBoth(const BtbBlockStore *store,
                                 BtbNote *snapshot, int *hasSnapshot,
                                 BtbNote *journal, int *hasJournal)
{
    unsigned char raw[BTB_SECTOR_BYTES];
    if (BtbStorageReadStable(store, BTB_NOTE_SNAPSHOT_SECTOR, raw) != BTB_STORAGE_OK)
        return BTB_JOURNAL_INVALID_ARGUMENT;
    BtbJournalStatus result = DecodeRecord(raw, 'S', snapshot, hasSnapshot);
    if (result != BTB_JOURNAL_OK) return result;
    if (BtbStorageReadStable(store, BTB_NOTE_JOURNAL_SECTOR, raw) != BTB_STORAGE_OK)
        return BTB_JOURNAL_INVALID_ARGUMENT;
    result = DecodeRecord(raw, 'J', journal, hasJournal);
    if (result != BTB_JOURNAL_OK) return result;
    if (*hasJournal != 0 && *hasSnapshot != 0) {
        if (journal->revision < snapshot->revision ||
            journal->revision - snapshot->revision > UINT64_C(1)) return BTB_JOURNAL_CORRUPT;
        if (journal->revision == snapshot->revision &&
            strcmp(journal->text, snapshot->text) != 0) return BTB_JOURNAL_CORRUPT;
    }
    if (*hasJournal != 0 && *hasSnapshot == 0 && journal->revision != 1U)
        return BTB_JOURNAL_CORRUPT;
    if (*hasJournal == 0 && *hasSnapshot != 0)
        return BTB_JOURNAL_CORRUPT; /* This lab never discards its journal. */
    return BTB_JOURNAL_OK;
}

BtbJournalStatus BtbJournalRead(const BtbBlockStore *store, BtbNote *output)
{
    if (store == NULL || output == NULL) return BTB_JOURNAL_INVALID_ARGUMENT;
    BtbNote snapshot = {0}, journal = {0};
    int hasSnapshot = 0, hasJournal = 0;
    const BtbJournalStatus status = ReadBoth(store, &snapshot, &hasSnapshot, &journal, &hasJournal);
    if (status != BTB_JOURNAL_OK) return status;
    const BtbNote latest = hasJournal != 0 && (hasSnapshot == 0 || journal.revision > snapshot.revision)
                         ? journal : snapshot;
    *output = latest;
    return BTB_JOURNAL_OK;
}

static BtbJournalStatus FlushAll(BtbBlockStore *store)
{
    BtbFlushReport report;
    return BtbStorageFlush(store, SIZE_MAX, &report) == BTB_STORAGE_OK
           ? BTB_JOURNAL_OK : BTB_JOURNAL_IO_ERROR;
}

BtbJournalStatus BtbJournalCommit(BtbBlockStore *store, uint64_t expectedRevision,
                                   const char *text, BtbCommitHalt halt)
{
    if (store == NULL || text == NULL || (unsigned)halt > (unsigned)BTB_STOP_AFTER_SNAPSHOT_STAGE)
        return BTB_JOURNAL_INVALID_ARGUMENT;
    size_t length = 0U;
    while (length < BTB_NOTE_TEXT_CAPACITY && text[length] != '\0') ++length;
    if (length == BTB_NOTE_TEXT_CAPACITY) return BTB_JOURNAL_INVALID_ARGUMENT;
    if (BtbStorageHasDirty(store)) return BTB_JOURNAL_NEEDS_RECOVERY;
    BtbNote snapshot = {0}, journal = {0};
    int hasSnapshot = 0, hasJournal = 0;
    BtbJournalStatus status = ReadBoth(store, &snapshot, &hasSnapshot, &journal, &hasJournal);
    if (status != BTB_JOURNAL_OK) return status;
    if (hasJournal != 0 && (hasSnapshot == 0 || journal.revision > snapshot.revision))
        return BTB_JOURNAL_NEEDS_RECOVERY;
    const uint64_t currentRevision = hasSnapshot != 0 ? snapshot.revision : 0U;
    if (expectedRevision != currentRevision) return BTB_JOURNAL_CONFLICT;
    if (currentRevision == UINT64_MAX) return BTB_JOURNAL_EXHAUSTED;

    BtbNote next = {0};
    next.revision = currentRevision + 1U;
    memcpy(next.text, text, length);
    next.text[length] = '\0';
    unsigned char record[BTB_SECTOR_BYTES];
    EncodeRecord(&next, 'J', record);
    if (BtbStorageStage(store, BTB_NOTE_JOURNAL_SECTOR, record) != BTB_STORAGE_OK)
        return BTB_JOURNAL_IO_ERROR;
    if (halt == BTB_STOP_BEFORE_JOURNAL_FLUSH) return BTB_JOURNAL_INTERRUPTED;
    status = FlushAll(store);
    if (status != BTB_JOURNAL_OK) return status;
    if (halt == BTB_STOP_AFTER_JOURNAL_FLUSH) return BTB_JOURNAL_INTERRUPTED;

    EncodeRecord(&next, 'S', record);
    if (BtbStorageStage(store, BTB_NOTE_SNAPSHOT_SECTOR, record) != BTB_STORAGE_OK)
        return BTB_JOURNAL_IO_ERROR;
    if (halt == BTB_STOP_AFTER_SNAPSHOT_STAGE) return BTB_JOURNAL_INTERRUPTED;
    return FlushAll(store);
}

BtbJournalStatus BtbJournalRecover(BtbBlockStore *store, BtbNote *output)
{
    if (store == NULL || output == NULL) return BTB_JOURNAL_INVALID_ARGUMENT;
    /* Reboot discards staged state before making any recovery decision. */
    BtbStorageCrash(store);
    BtbNote snapshot = {0}, journal = {0};
    int hasSnapshot = 0, hasJournal = 0;
    BtbJournalStatus status = ReadBoth(store, &snapshot, &hasSnapshot, &journal, &hasJournal);
    if (status != BTB_JOURNAL_OK) return status;
    if (hasJournal != 0 && (hasSnapshot == 0 || journal.revision > snapshot.revision)) {
        unsigned char record[BTB_SECTOR_BYTES];
        EncodeRecord(&journal, 'S', record);
        if (BtbStorageStage(store, BTB_NOTE_SNAPSHOT_SECTOR, record) != BTB_STORAGE_OK)
            return BTB_JOURNAL_IO_ERROR;
        status = FlushAll(store);
        if (status != BTB_JOURNAL_OK) return status;
    }
    return BtbJournalRead(store, output);
}
