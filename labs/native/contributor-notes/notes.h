/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/contributor-notes/notes.h
 * PURPOSE: Small bounded, in-memory notes model for the first native build.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *
 * Educational code. This is NOT a second Umicom Framework document store.
 * It does not persist, use a database, launch tools or inspect Git state.
 *---------------------------------------------------------------------------*/
#ifndef BTB_CONTRIBUTOR_NOTES_H
#define BTB_CONTRIBUTOR_NOTES_H

#include <stddef.h>
#include <stdint.h>

#define BTB_NOTES_CAPACITY 8U
#define BTB_NOTE_TEXT_CAPACITY 96U

typedef enum BtbNotesResult {
    BTB_NOTES_OK = 0,
    BTB_NOTES_INVALID,
    BTB_NOTES_FULL,
    BTB_NOTES_TOO_LONG,
    BTB_NOTES_NOT_FOUND
} BtbNotesResult;

typedef struct BtbNote {
    uint32_t id;
    char text[BTB_NOTE_TEXT_CAPACITY];
} BtbNote;

typedef struct BtbNoteStore {
    BtbNote notes[BTB_NOTES_CAPACITY];
    size_t count;
    uint32_t nextId;
} BtbNoteStore;

/* The caller owns the store. No pointers are retained; no function allocates.
 * Invalid operations leave the entire store and any output arguments unchanged.
 * A null-terminated text value must fit INCLUDING its terminator.
 * The store is used by one thread only; it is not safe for concurrent mutation. */
BtbNotesResult BtbNotesInit(BtbNoteStore *store);
BtbNotesResult BtbNotesAdd(BtbNoteStore *store, const char *text, uint32_t *outId);
BtbNotesResult BtbNotesUpdate(BtbNoteStore *store, uint32_t id, const char *text);
BtbNotesResult BtbNotesRead(const BtbNoteStore *store, uint32_t id, BtbNote *outNote);
BtbNotesResult BtbNotesAt(const BtbNoteStore *store, size_t index, BtbNote *outNote);
size_t BtbNotesCount(const BtbNoteStore *store);

#endif
