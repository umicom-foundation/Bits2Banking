/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/fault-injection/note.h
 * PURPOSE: Teach explicit memory ownership and failure-atomic replacement.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BTB_FAULT_INJECTION_NOTE_H
#define BTB_FAULT_INJECTION_NOTE_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BTB_MAX_TEXT_BYTES 80U

typedef void *(*BtbAllocateFn)(size_t size, void *context);
typedef void (*BtbReleaseFn)(void *pointer, void *context);
typedef struct BtbAllocator {
    BtbAllocateFn allocate;
    BtbReleaseFn release;
    void *context;
} BtbAllocator;

typedef enum BtbStatus {
    BTB_OK = 0,
    BTB_INVALID = 1,
    BTB_NO_MEMORY = 2,
    BTB_CONFLICT = 3,
    BTB_LIMIT = 4
} BtbStatus;

typedef struct BtbNote {
    BtbAllocator allocator;
    char *title;
    char *body;
    uint64_t revision;
} BtbNote;

/* Create on zero-initialised storage. Input is a readable byte span of the
 * supplied size, not necessarily a NUL-terminated string. Data is copied.
 * Refused creation does not transfer ownership to the note. */
BtbStatus BtbNoteInit(BtbNote *note, BtbAllocator allocator,
                      const char *title, size_t titleBytes,
                      const char *body, size_t bodyBytes);
/* Build both replacements before committing either; stale revisions, invalid
 * bytes or a failed allocation leave existing content and revision unchanged. */
BtbStatus BtbNoteReplace(BtbNote *note, uint64_t expectedRevision,
                         const char *title, size_t titleBytes,
                         const char *body, size_t bodyBytes);
/* Reading title/body yields borrowed pointers until the next successful
 * replacement or destruction. The caller must not modify or free them. */
const char *BtbNoteTitle(const BtbNote *note);
const char *BtbNoteBody(const BtbNote *note);
uint64_t BtbNoteRevision(const BtbNote *note);
void BtbNoteDestroy(BtbNote *note);
#ifdef __cplusplus
}
#endif
#endif
