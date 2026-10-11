/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/fault-injection/note.c
 * PURPOSE: Copy two fields and publish only after both allocations succeed.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "note.h"
#include <string.h>
#include <stdint.h>

/* A span length is checked before looking at any of its bytes. Embedded NUL
 * is refused because this particular Notes representation promises C strings. */
static BtbStatus Validate(const char *bytes, size_t length, int allowEmpty)
{
    if (bytes == NULL || (!allowEmpty && length == 0U)) return BTB_INVALID;
    if (length > BTB_MAX_TEXT_BYTES) return BTB_LIMIT;
    if (memchr(bytes, '\0', length) != NULL) return BTB_INVALID;
    return BTB_OK;
}

static BtbStatus CopyPair(BtbAllocator allocator,
                          const char *title, size_t titleBytes,
                          const char *body, size_t bodyBytes,
                          char **newTitle, char **newBody)
{
    if (allocator.allocate == NULL || allocator.release == NULL ||
        newTitle == NULL || newBody == NULL) return BTB_INVALID;
    BtbStatus status = Validate(title, titleBytes, 0);
    if (status != BTB_OK) return status;
    status = Validate(body, bodyBytes, 1);
    if (status != BTB_OK) return status;

    char *titleCopy = allocator.allocate(titleBytes + 1U, allocator.context);
    if (titleCopy == NULL) return BTB_NO_MEMORY;
    char *bodyCopy = allocator.allocate(bodyBytes + 1U, allocator.context);
    if (bodyCopy == NULL) {
        allocator.release(titleCopy, allocator.context);
        return BTB_NO_MEMORY;
    }
    memcpy(titleCopy, title, titleBytes);
    titleCopy[titleBytes] = '\0';
    memcpy(bodyCopy, body, bodyBytes);
    bodyCopy[bodyBytes] = '\0';
    *newTitle = titleCopy;
    *newBody = bodyCopy;
    return BTB_OK;
}

BtbStatus BtbNoteInit(BtbNote *note, BtbAllocator allocator,
                      const char *title, size_t titleBytes,
                      const char *body, size_t bodyBytes)
{
    if (note == NULL || note->revision != 0U || note->title != NULL ||
        note->body != NULL) return BTB_INVALID;
    char *ownedTitle = NULL;
    char *ownedBody = NULL;
    BtbStatus status = CopyPair(allocator, title, titleBytes, body, bodyBytes,
                                &ownedTitle, &ownedBody);
    if (status != BTB_OK) return status;
    note->allocator = allocator;
    note->title = ownedTitle;
    note->body = ownedBody;
    note->revision = 1U;
    return BTB_OK;
}

BtbStatus BtbNoteReplace(BtbNote *note, uint64_t expectedRevision,
                         const char *title, size_t titleBytes,
                         const char *body, size_t bodyBytes)
{
    if (note == NULL || note->revision == 0U || note->title == NULL ||
        note->body == NULL) return BTB_INVALID;
    if (note->revision != expectedRevision) return BTB_CONFLICT;
    if (note->revision == UINT64_MAX) return BTB_LIMIT;

    char *ownedTitle = NULL;
    char *ownedBody = NULL;
    BtbStatus status = CopyPair(note->allocator, title, titleBytes, body, bodyBytes,
                                &ownedTitle, &ownedBody);
    if (status != BTB_OK) return status;
    note->allocator.release(note->title, note->allocator.context);
    note->allocator.release(note->body, note->allocator.context);
    note->title = ownedTitle;
    note->body = ownedBody;
    ++note->revision;
    return BTB_OK;
}

const char *BtbNoteTitle(const BtbNote *note)
{
    return note == NULL ? NULL : note->title;
}
const char *BtbNoteBody(const BtbNote *note)
{
    return note == NULL ? NULL : note->body;
}
uint64_t BtbNoteRevision(const BtbNote *note)
{
    return note == NULL ? 0U : note->revision;
}
void BtbNoteDestroy(BtbNote *note)
{
    if (note == NULL) return;
    if (note->allocator.release != NULL) {
        if (note->title != NULL) note->allocator.release(note->title, note->allocator.context);
        if (note->body != NULL) note->allocator.release(note->body, note->allocator.context);
    }
    *note = (BtbNote){0};
}
