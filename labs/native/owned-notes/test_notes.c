/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/owned-notes/test_notes.c
 * PURPOSE: Test ownership, exact reads, atomic replacement and capacity edges.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>
#include <string.h>

#define CHECK(condition) do {                                                   \
    if (!(condition)) {                                                         \
        (void)fprintf(stderr, "FAILED %s:%d: %s\n", __FILE__, __LINE__, #condition); \
        return 1;                                                               \
    }                                                                           \
} while (0)

int main(void)
{
    BtbNoteStore *store = NULL;
    CHECK(BtbNoteStoreCreate(NULL) == BTB_NOTE_INVALID_ARGUMENT);
    CHECK(BtbNoteStoreCreate(&store) == BTB_NOTE_OK);
    CHECK(BtbNoteStoreCount(store) == 0U);
    CHECK(BtbNoteStoreCount(NULL) == 0U);

    char titleInput[] = "First note";
    char bodyInput[] = "Write an Umicom Notes model.";
    BtbNoteId id = 9999U;
    CHECK(BtbNoteStoreAdd(store, titleInput, bodyInput, &id) == BTB_NOTE_OK);
    CHECK(id == 1U);
    titleInput[0] = 'X';
    bodyInput[0] = 'X';

    char title[BTB_NOTES_MAX_TITLE_BYTES + 1U];
    char body[BTB_NOTES_MAX_BODY_BYTES + 1U];
    CHECK(BtbNoteStoreRead(store, id, title, sizeof(title), body, sizeof(body)) == BTB_NOTE_OK);
    CHECK(strcmp(title, "First note") == 0);
    CHECK(strcmp(body, "Write an Umicom Notes model.") == 0);
    CHECK(BtbNoteStoreCount(store) == 1U);

    char tinyTitle[] = "KEEP";
    char tinyBody[] = "KEEP";
    CHECK(BtbNoteStoreRead(store, id, tinyTitle, sizeof(tinyTitle), tinyBody, sizeof(tinyBody))
          == BTB_NOTE_CAPACITY_EXCEEDED);
    CHECK(strcmp(tinyTitle, "KEEP") == 0);
    CHECK(strcmp(tinyBody, "KEEP") == 0);
    CHECK(BtbNoteStoreRead(store, 0U, title, sizeof(title), body, sizeof(body))
          == BTB_NOTE_NOT_FOUND);
    CHECK(BtbNoteStoreRead(NULL, id, title, sizeof(title), body, sizeof(body))
          == BTB_NOTE_INVALID_ARGUMENT);

    char tooLong[BTB_NOTES_MAX_BODY_BYTES + 2U];
    memset(tooLong, 'A', sizeof(tooLong));
    tooLong[sizeof(tooLong) - 1U] = '\0';
    CHECK(BtbNoteStoreReplace(store, id, "Proposed title", tooLong)
          == BTB_NOTE_INVALID_ARGUMENT);
    CHECK(BtbNoteStoreRead(store, id, title, sizeof(title), body, sizeof(body)) == BTB_NOTE_OK);
    CHECK(strcmp(title, "First note") == 0);
    CHECK(BtbNoteStoreReplace(store, id, "Reviewed note", "Tests passed.") == BTB_NOTE_OK);
    CHECK(BtbNoteStoreRead(store, id, title, sizeof(title), body, sizeof(body)) == BTB_NOTE_OK);
    CHECK(strcmp(title, "Reviewed note") == 0);
    CHECK(strcmp(body, "Tests passed.") == 0);

    BtbNoteId next = 0U;
    CHECK(BtbNoteStoreAdd(store, "Second note", "Body", &next) == BTB_NOTE_OK);
    CHECK(next == 2U);
    CHECK(BtbNoteStoreRemove(store, id) == BTB_NOTE_OK);
    CHECK(BtbNoteStoreCount(store) == 1U);
    CHECK(BtbNoteStoreRead(store, next, title, sizeof(title), body, sizeof(body)) == BTB_NOTE_OK);
    CHECK(strcmp(title, "Second note") == 0);
    CHECK(BtbNoteStoreRemove(store, id) == BTB_NOTE_NOT_FOUND);
    CHECK(BtbNoteStoreRemove(NULL, next) == BTB_NOTE_INVALID_ARGUMENT);

    for (size_t index = 1U; index < BTB_NOTES_MAX_COUNT; ++index)
        CHECK(BtbNoteStoreAdd(store, "Task", "Review", &next) == BTB_NOTE_OK);
    CHECK(BtbNoteStoreCount(store) == BTB_NOTES_MAX_COUNT);
    next = UINT32_MAX;
    CHECK(BtbNoteStoreAdd(store, "Too many", "Not accepted", &next)
          == BTB_NOTE_CAPACITY_EXCEEDED);
    CHECK(next == UINT32_MAX);
    CHECK(BtbNoteStoreCount(store) == BTB_NOTES_MAX_COUNT);

    BtbNoteStoreDestroy(store);
    BtbNoteStoreDestroy(NULL);
    puts("Owned Notes: deep copy, atomic edits, buffer bounds and maximum count passed.");
    return 0;
}
