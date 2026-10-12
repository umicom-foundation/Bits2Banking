/*-----------------------------------------------------------------------------
 * Bits2Banking — Umicom Foundation
 * File: labs/native/journalled-notes/journal.h
 * PURPOSE: A one-note write-ahead journal using the shared sector simulator.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_NOTES_JOURNAL_H
#define BTB_NOTES_JOURNAL_H

#include "block_store.h"
#include <stdint.h>

#define BTB_NOTE_TEXT_CAPACITY 81U
#define BTB_NOTE_JOURNAL_SECTOR 0U
#define BTB_NOTE_SNAPSHOT_SECTOR 1U

typedef struct BtbNote {
    uint64_t revision;
    char text[BTB_NOTE_TEXT_CAPACITY];
} BtbNote;

typedef enum BtbJournalStatus {
    BTB_JOURNAL_OK = 0,
    BTB_JOURNAL_INVALID_ARGUMENT,
    BTB_JOURNAL_CORRUPT,
    BTB_JOURNAL_CONFLICT,
    BTB_JOURNAL_NEEDS_RECOVERY,
    BTB_JOURNAL_INTERRUPTED,
    BTB_JOURNAL_IO_ERROR,
    BTB_JOURNAL_EXHAUSTED
} BtbJournalStatus;

typedef enum BtbCommitHalt {
    BTB_COMMIT_COMPLETE = 0,
    BTB_STOP_BEFORE_JOURNAL_FLUSH,
    BTB_STOP_AFTER_JOURNAL_FLUSH,
    BTB_STOP_AFTER_SNAPSHOT_STAGE
} BtbCommitHalt;

/* Read only the simulated stable copy. Never read a still-staged write as if
 * it were durable. On failure, the caller's output remains unchanged. */
BtbJournalStatus BtbJournalRead(const BtbBlockStore *store, BtbNote *output);
/* An accepted transaction is first flushed as a journal sector, then as a
 * snapshot sector. Halt points simulate interruption; caller must call
 * BtbJournalRecover before trying another commit. */
BtbJournalStatus BtbJournalCommit(BtbBlockStore *store, uint64_t expectedRevision,
                                   const char *text, BtbCommitHalt halt);
/* Discard volatile staged writes, validate both copies, and replay a newer
 * durable journal entry into the snapshot sector. The simulated flush assumes
 * atomic 512-byte sectors; this is not a real filesystem crash protocol. */
BtbJournalStatus BtbJournalRecover(BtbBlockStore *store, BtbNote *output);

#endif
