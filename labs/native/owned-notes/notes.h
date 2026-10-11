/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/owned-notes/notes.h
 * PURPOSE: A small owned-memory Notes model for learning C23 contracts.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS2BANKING_OWNED_NOTES_H
#define BITS2BANKING_OWNED_NOTES_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BTB_NOTES_MAX_COUNT 64U
#define BTB_NOTES_MAX_TITLE_BYTES 80U
#define BTB_NOTES_MAX_BODY_BYTES 4096U

typedef struct BtbNoteStore BtbNoteStore;
typedef uint32_t BtbNoteId;
typedef enum BtbNoteStatus {
    BTB_NOTE_OK = 0,
    BTB_NOTE_INVALID_ARGUMENT = 1,
    BTB_NOTE_NOT_FOUND = 2,
    BTB_NOTE_CAPACITY_EXCEEDED = 3,
    BTB_NOTE_OUT_OF_MEMORY = 4
} BtbNoteStatus;

/* Create a private owner. On failure *outStore remains NULL. */
BtbNoteStatus BtbNoteStoreCreate(BtbNoteStore **outStore);
/* Release every note and its text. Passing NULL is harmless. */
void BtbNoteStoreDestroy(BtbNoteStore *store);
size_t BtbNoteStoreCount(const BtbNoteStore *store);
/* The store makes deep copies. Callers retain ownership of their input strings.
 * title must be nonempty; body may be empty. Inputs must be NUL-terminated.
 * A rejected call leaves the store and outId unchanged. */
BtbNoteStatus BtbNoteStoreAdd(BtbNoteStore *store, const char *title,
                              const char *body, BtbNoteId *outId);
/* An exact note lookup copies text into caller storage. Either too-small buffer
 * refuses the whole operation and leaves both caller buffers unchanged. */
BtbNoteStatus BtbNoteStoreRead(const BtbNoteStore *store, BtbNoteId id,
                               char *title, size_t titleCapacity,
                               char *body, size_t bodyCapacity);
/* Allocate both replacement strings before releasing the old ones. */
BtbNoteStatus BtbNoteStoreReplace(BtbNoteStore *store, BtbNoteId id,
                                  const char *title, const char *body);
/* Remove one note; later IDs remain stable rather than moving with the array. */
BtbNoteStatus BtbNoteStoreRemove(BtbNoteStore *store, BtbNoteId id);
const char *BtbNoteStatusText(BtbNoteStatus status);
#ifdef __cplusplus
}
#endif
#endif
