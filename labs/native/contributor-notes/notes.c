/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/contributor-notes/notes.c
 * PURPOSE: Checked educational notes operations using caller-owned storage.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"

#include <limits.h>
#include <string.h>

/* Validate a bounded C string without reading past its permitted storage.
 * The caller must still supply an accessible NUL-terminated string, whose
 * address is valid for at least the inspected bytes. */
static BtbNotesResult CheckText(const char *text, size_t *outLength)
{
    size_t index;
    if (text == NULL || outLength == NULL) return BTB_NOTES_INVALID;
    for (index = 0U; index < BTB_NOTE_TEXT_CAPACITY; ++index) {
        if (text[index] == '\0') {
            if (index == 0U) return BTB_NOTES_INVALID;
            *outLength = index;
            return BTB_NOTES_OK;
        }
    }
    return BTB_NOTES_TOO_LONG;
}

static int ValidStore(const BtbNoteStore *store)
{
    size_t index;
    if (store == NULL || store->count > BTB_NOTES_CAPACITY || store->nextId == 0U)
        return 0;
    for (index = 0U; index < store->count; ++index) {
        if (store->notes[index].id == 0U ||
            memchr(store->notes[index].text, '\0', BTB_NOTE_TEXT_CAPACITY) == NULL)
            return 0;
    }
    return 1;
}

BtbNotesResult BtbNotesInit(BtbNoteStore *store)
{
    if (store == NULL) return BTB_NOTES_INVALID;
    *store = (BtbNoteStore){ .nextId = 1U };
    return BTB_NOTES_OK;
}

BtbNotesResult BtbNotesAdd(BtbNoteStore *store, const char *text, uint32_t *outId)
{
    size_t length;
    BtbNotesResult result;
    BtbNote candidate = {0};
    if (!ValidStore(store) || outId == NULL) return BTB_NOTES_INVALID;
    result = CheckText(text, &length);
    if (result != BTB_NOTES_OK) return result;
    if (store->count == BTB_NOTES_CAPACITY) return BTB_NOTES_FULL;
    /* UINT32_MAX is reserved: never wrap the next identifier back to zero. */
    if (store->nextId == UINT32_MAX) return BTB_NOTES_FULL;
    candidate.id = store->nextId;
    (void)memcpy(candidate.text, text, length + 1U);
    store->notes[store->count] = candidate;
    ++store->count;
    ++store->nextId;
    *outId = candidate.id;
    return BTB_NOTES_OK;
}

BtbNotesResult BtbNotesUpdate(BtbNoteStore *store, uint32_t id, const char *text)
{
    size_t length;
    size_t index;
    BtbNotesResult result;
    BtbNote candidate;
    if (!ValidStore(store) || id == 0U) return BTB_NOTES_INVALID;
    result = CheckText(text, &length);
    if (result != BTB_NOTES_OK) return result;
    for (index = 0U; index < store->count; ++index) {
        if (store->notes[index].id == id) {
            candidate = (BtbNote){.id = id};
            (void)memcpy(candidate.text, text, length + 1U);
            store->notes[index] = candidate;
            return BTB_NOTES_OK;
        }
    }
    return BTB_NOTES_NOT_FOUND;
}

BtbNotesResult BtbNotesRead(const BtbNoteStore *store, uint32_t id, BtbNote *outNote)
{
    size_t index;
    if (!ValidStore(store) || outNote == NULL || id == 0U) return BTB_NOTES_INVALID;
    for (index = 0U; index < store->count; ++index) {
        if (store->notes[index].id == id) {
            *outNote = store->notes[index];
            return BTB_NOTES_OK;
        }
    }
    return BTB_NOTES_NOT_FOUND;
}

BtbNotesResult BtbNotesAt(const BtbNoteStore *store, size_t index, BtbNote *outNote)
{
    if (!ValidStore(store) || outNote == NULL) return BTB_NOTES_INVALID;
    if (index >= store->count) return BTB_NOTES_NOT_FOUND;
    *outNote = store->notes[index];
    return BTB_NOTES_OK;
}

size_t BtbNotesCount(const BtbNoteStore *store)
{
    return ValidStore(store) ? store->count : 0U;
}
