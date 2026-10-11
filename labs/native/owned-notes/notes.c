/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/owned-notes/notes.c
 * PURPOSE: Teach ownership, checked capacity growth and failure-atomic edits.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct BtbOwnedNote {
    BtbNoteId id;
    char *title;
    char *body;
} BtbOwnedNote;

struct BtbNoteStore {
    BtbOwnedNote *notes;
    size_t count;
    size_t capacity;
    BtbNoteId nextId;
};

/* Do not search indefinitely for a NUL terminator. This helper requires a
 * valid readable C string of at least the maximum inspected length. */
static int BtbBoundedLength(const char *text, size_t limit, size_t *length)
{
    if (text == NULL || length == NULL) return 0;
    for (size_t index = 0U; index <= limit; ++index) {
        if (text[index] == '\0') {
            *length = index;
            return 1;
        }
    }
    return 0;
}

/* Allocation is kept separate from publication. Failed replacement cannot
 * destroy the earlier title/body, even when the second allocation fails. */
static BtbNoteStatus BtbOwnedCopy(const char *text, size_t maximum,
                                  int mustNotBeEmpty, char **outCopy)
{
    size_t length = 0U;
    if (outCopy == NULL || !BtbBoundedLength(text, maximum, &length) ||
        (mustNotBeEmpty && length == 0U)) return BTB_NOTE_INVALID_ARGUMENT;
    char *result = malloc(length + 1U);
    if (result == NULL) return BTB_NOTE_OUT_OF_MEMORY;
    memcpy(result, text, length + 1U);
    *outCopy = result;
    return BTB_NOTE_OK;
}

static BtbNoteStatus BtbOwnedPair(const char *title, const char *body,
                                  char **outTitle, char **outBody)
{
    char *newTitle = NULL;
    char *newBody = NULL;
    BtbNoteStatus status = BtbOwnedCopy(title, BTB_NOTES_MAX_TITLE_BYTES,
                                        1, &newTitle);
    if (status == BTB_NOTE_OK)
        status = BtbOwnedCopy(body, BTB_NOTES_MAX_BODY_BYTES, 0, &newBody);
    if (status != BTB_NOTE_OK) {
        free(newTitle);
        free(newBody);
        return status;
    }
    *outTitle = newTitle;
    *outBody = newBody;
    return BTB_NOTE_OK;
}

static BtbNoteStatus BtbReserve(BtbNoteStore *store)
{
    if (store->count < store->capacity) return BTB_NOTE_OK;
    if (store->capacity >= BTB_NOTES_MAX_COUNT) return BTB_NOTE_CAPACITY_EXCEEDED;
    size_t newCapacity = store->capacity == 0U ? 4U : store->capacity * 2U;
    if (newCapacity > BTB_NOTES_MAX_COUNT) newCapacity = BTB_NOTES_MAX_COUNT;
    if (newCapacity > SIZE_MAX / sizeof(*store->notes))
        return BTB_NOTE_CAPACITY_EXCEEDED;
    /* Retain the original pointer when realloc cannot allocate storage. */
    BtbOwnedNote *enlarged = realloc(store->notes, newCapacity * sizeof(*enlarged));
    if (enlarged == NULL) return BTB_NOTE_OUT_OF_MEMORY;
    store->notes = enlarged;
    store->capacity = newCapacity;
    return BTB_NOTE_OK;
}

static size_t BtbFindIndex(const BtbNoteStore *store, BtbNoteId id)
{
    if (store == NULL || id == 0U) return SIZE_MAX;
    for (size_t index = 0U; index < store->count; ++index)
        if (store->notes[index].id == id) return index;
    return SIZE_MAX;
}

BtbNoteStatus BtbNoteStoreCreate(BtbNoteStore **outStore)
{
    if (outStore == NULL) return BTB_NOTE_INVALID_ARGUMENT;
    *outStore = NULL;
    BtbNoteStore *store = calloc(1U, sizeof(*store));
    if (store == NULL) return BTB_NOTE_OUT_OF_MEMORY;
    store->nextId = 1U;
    *outStore = store;
    return BTB_NOTE_OK;
}

void BtbNoteStoreDestroy(BtbNoteStore *store)
{
    if (store == NULL) return;
    for (size_t index = 0U; index < store->count; ++index) {
        free(store->notes[index].title);
        free(store->notes[index].body);
    }
    free(store->notes);
    free(store);
}

size_t BtbNoteStoreCount(const BtbNoteStore *store)
{
    return store == NULL ? 0U : store->count;
}

BtbNoteStatus BtbNoteStoreAdd(BtbNoteStore *store, const char *title,
                              const char *body, BtbNoteId *outId)
{
    if (store == NULL || outId == NULL) return BTB_NOTE_INVALID_ARGUMENT;
    if (store->count >= BTB_NOTES_MAX_COUNT) return BTB_NOTE_CAPACITY_EXCEEDED;
    if (store->nextId == 0U || store->nextId == UINT32_MAX)
        return BTB_NOTE_CAPACITY_EXCEEDED;
    char *newTitle = NULL;
    char *newBody = NULL;
    BtbNoteStatus status = BtbOwnedPair(title, body, &newTitle, &newBody);
    if (status != BTB_NOTE_OK) return status;
    status = BtbReserve(store);
    if (status != BTB_NOTE_OK) {
        free(newTitle);
        free(newBody);
        return status;
    }
    BtbNoteId id = store->nextId;
    store->notes[store->count] = (BtbOwnedNote){id, newTitle, newBody};
    ++store->count;
    ++store->nextId;
    *outId = id;
    return BTB_NOTE_OK;
}

BtbNoteStatus BtbNoteStoreRead(const BtbNoteStore *store, BtbNoteId id,
                               char *title, size_t titleCapacity,
                               char *body, size_t bodyCapacity)
{
    if (store == NULL || title == NULL || body == NULL ||
        titleCapacity == 0U || bodyCapacity == 0U) return BTB_NOTE_INVALID_ARGUMENT;
    size_t index = BtbFindIndex(store, id);
    if (index == SIZE_MAX) return BTB_NOTE_NOT_FOUND;
    const BtbOwnedNote *note = &store->notes[index];
    size_t titleBytes = strlen(note->title) + 1U;
    size_t bodyBytes = strlen(note->body) + 1U;
    if (titleBytes > titleCapacity || bodyBytes > bodyCapacity)
        return BTB_NOTE_CAPACITY_EXCEEDED;
    memcpy(title, note->title, titleBytes);
    memcpy(body, note->body, bodyBytes);
    return BTB_NOTE_OK;
}

BtbNoteStatus BtbNoteStoreReplace(BtbNoteStore *store, BtbNoteId id,
                                  const char *title, const char *body)
{
    size_t index = BtbFindIndex(store, id);
    if (index == SIZE_MAX) return store == NULL || id == 0U
                              ? BTB_NOTE_INVALID_ARGUMENT : BTB_NOTE_NOT_FOUND;
    char *newTitle = NULL;
    char *newBody = NULL;
    BtbNoteStatus status = BtbOwnedPair(title, body, &newTitle, &newBody);
    if (status != BTB_NOTE_OK) return status;
    free(store->notes[index].title);
    free(store->notes[index].body);
    store->notes[index].title = newTitle;
    store->notes[index].body = newBody;
    return BTB_NOTE_OK;
}

BtbNoteStatus BtbNoteStoreRemove(BtbNoteStore *store, BtbNoteId id)
{
    size_t index = BtbFindIndex(store, id);
    if (index == SIZE_MAX) return store == NULL || id == 0U
                              ? BTB_NOTE_INVALID_ARGUMENT : BTB_NOTE_NOT_FOUND;
    free(store->notes[index].title);
    free(store->notes[index].body);
    if (index + 1U < store->count)
        memmove(&store->notes[index], &store->notes[index + 1U],
                (store->count - index - 1U) * sizeof(*store->notes));
    --store->count;
    return BTB_NOTE_OK;
}

const char *BtbNoteStatusText(BtbNoteStatus status)
{
    switch (status) {
    case BTB_NOTE_OK: return "OK";
    case BTB_NOTE_INVALID_ARGUMENT: return "invalid argument";
    case BTB_NOTE_NOT_FOUND: return "note not found";
    case BTB_NOTE_CAPACITY_EXCEEDED: return "capacity exceeded";
    case BTB_NOTE_OUT_OF_MEMORY: return "out of memory";
    default: return "unknown status";
    }
}
