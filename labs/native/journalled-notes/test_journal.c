/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/journalled-notes/test_journal.c
 * PURPOSE: Test write-ahead ordering, interruptions, replay, conflict and
 *          evidence corruption without an actual power interruption.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "journal.h"
#include <stdio.h>
#include <string.h>

#define REQUIRE(condition) do { if (!(condition)) { \
    fprintf(stderr, "%s:%d failed: %s\n", __FILE__, __LINE__, #condition); return 1; \
} } while (0)

int main(void)
{
    BtbBlockStore store;
    BtbStorageInit(&store);
    BtbNote note = {0};
    REQUIRE(BtbJournalRead(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 0U && note.text[0] == '\0');
    REQUIRE(BtbJournalCommit(&store, 0U, "Quarterly cash plan", BTB_COMMIT_COMPLETE) == BTB_JOURNAL_OK);
    REQUIRE(BtbJournalRead(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 1U && strcmp(note.text, "Quarterly cash plan") == 0);
    REQUIRE(BtbJournalCommit(&store, 0U, "Stale revision", BTB_COMMIT_COMPLETE) == BTB_JOURNAL_CONFLICT);
    char tooLong[BTB_NOTE_TEXT_CAPACITY + 4U];
    memset(tooLong, 'X', sizeof(tooLong));
    tooLong[sizeof(tooLong) - 1U] = '\0';
    REQUIRE(BtbJournalCommit(&store, 1U, tooLong, BTB_COMMIT_COMPLETE) == BTB_JOURNAL_INVALID_ARGUMENT);
    REQUIRE(!BtbStorageHasDirty(&store));

    /* Stop before the first flush: no accepted journal bytes survive crash. */
    REQUIRE(BtbJournalCommit(&store, 1U, "Not yet accepted", BTB_STOP_BEFORE_JOURNAL_FLUSH) == BTB_JOURNAL_INTERRUPTED);
    REQUIRE(BtbStorageHasDirty(&store));
    REQUIRE(BtbJournalCommit(&store, 1U, "Unsafe retry", BTB_COMMIT_COMPLETE) == BTB_JOURNAL_NEEDS_RECOVERY);
    REQUIRE(BtbJournalRecover(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 1U && strcmp(note.text, "Quarterly cash plan") == 0);
    REQUIRE(!BtbStorageHasDirty(&store));

    /* The journal is stable, the snapshot is older: replay the accepted save. */
    REQUIRE(BtbJournalCommit(&store, 1U, "Approved budget note", BTB_STOP_AFTER_JOURNAL_FLUSH) == BTB_JOURNAL_INTERRUPTED);
    REQUIRE(BtbJournalCommit(&store, 2U, "No overwrite", BTB_COMMIT_COMPLETE) == BTB_JOURNAL_NEEDS_RECOVERY);
    REQUIRE(BtbJournalRecover(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 2U && strcmp(note.text, "Approved budget note") == 0);

    /* Crash after the snapshot is staged still replays stable journal data. */
    REQUIRE(BtbJournalCommit(&store, 2U, "Note after interrupted apply", BTB_STOP_AFTER_SNAPSHOT_STAGE) == BTB_JOURNAL_INTERRUPTED);
    REQUIRE(BtbStorageHasDirty(&store));
    REQUIRE(BtbJournalRecover(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 3U && strcmp(note.text, "Note after interrupted apply") == 0);
    REQUIRE(BtbJournalCommit(&store, 3U, "Completed checkpoint", BTB_COMMIT_COMPLETE) == BTB_JOURNAL_OK);
    REQUIRE(BtbJournalRead(&store, &note) == BTB_JOURNAL_OK);
    REQUIRE(note.revision == 4U);

    /* Every single-bit mutation of the complete journal sector must be
     * rejected, including changes in otherwise unused zero padding. This
     * preserves an existing successful output for all 4096 cases. */
    for (size_t byte = 0U; byte < BTB_SECTOR_BYTES; ++byte) {
        for (unsigned bit = 0U; bit < 8U; ++bit) {
            store.stable[BTB_NOTE_JOURNAL_SECTOR][byte] ^= (unsigned char)(1U << bit);
            note.revision = UINT64_C(991);
            memcpy(note.text, "untouched", sizeof("untouched"));
            REQUIRE(BtbJournalRead(&store, &note) == BTB_JOURNAL_CORRUPT);
            REQUIRE(note.revision == UINT64_C(991) && strcmp(note.text, "untouched") == 0);
            store.stable[BTB_NOTE_JOURNAL_SECTOR][byte] ^= (unsigned char)(1U << bit);
        }
    }
    /* Corruption must never masquerade as an empty journal or replace output. */
    note.revision = UINT64_C(991);
    memcpy(note.text, "untouched", sizeof("untouched"));
    store.stable[BTB_NOTE_JOURNAL_SECTOR][14] ^= 0xFFU; /* Corrupt CRC byte. */
    REQUIRE(BtbJournalRead(&store, &note) == BTB_JOURNAL_CORRUPT);
    REQUIRE(note.revision == UINT64_C(991) && strcmp(note.text, "untouched") == 0);
    REQUIRE(BtbJournalRecover(&store, &note) == BTB_JOURNAL_CORRUPT);
    REQUIRE(note.revision == UINT64_C(991));
    puts("WAL tests passed: replay, conflicts, interruption boundaries, corruption refusal.");
    return 0;
}
