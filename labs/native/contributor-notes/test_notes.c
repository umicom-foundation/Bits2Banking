/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/contributor-notes/test_notes.c
 * PURPOSE: Independent CTest-positive and negative tests for bounded Notes.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAILED at line %d: %s\n", __LINE__, #expr); return 1; \
} } while (0)

static int TestAdd(void)
{
    BtbNoteStore store;
    BtbNote note;
    uint32_t id = 99U;
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    CHECK(BtbNotesAdd(&store, "Prepare a banking Notes project", &id) == BTB_NOTES_OK);
    CHECK(id == 1U && BtbNotesCount(&store) == 1U);
    CHECK(BtbNotesRead(&store, id, &note) == BTB_NOTES_OK);
    CHECK(strcmp(note.text, "Prepare a banking Notes project") == 0);
    return 0;
}

static int TestUpdate(void)
{
    BtbNoteStore store;
    uint32_t id;
    BtbNote note;
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    CHECK(BtbNotesAdd(&store, "Draft note", &id) == BTB_NOTES_OK);
    CHECK(BtbNotesUpdate(&store, id, "Approved note") == BTB_NOTES_OK);
    CHECK(BtbNotesRead(&store, id, &note) == BTB_NOTES_OK);
    CHECK(strcmp(note.text, "Approved note") == 0);
    return 0;
}

static int TestTooLong(void)
{
    BtbNoteStore store;
    BtbNoteStore copy;
    uint32_t id = 321U;
    char longText[BTB_NOTE_TEXT_CAPACITY + 1U];
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    copy = store;
    (void)memset(longText, 'X', sizeof(longText));
    longText[sizeof(longText) - 1U] = '\0';
    CHECK(BtbNotesAdd(&store, longText, &id) == BTB_NOTES_TOO_LONG);
    CHECK(memcmp(&store, &copy, sizeof(store)) == 0 && id == 321U);
    return 0;
}

static int TestCapacity(void)
{
    BtbNoteStore store;
    BtbNoteStore copy;
    uint32_t id = 11U;
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    for (size_t index = 0U; index < BTB_NOTES_CAPACITY; ++index)
        CHECK(BtbNotesAdd(&store, "A real contributor note", &id) == BTB_NOTES_OK);
    copy = store;
    id = 1234U;
    CHECK(BtbNotesAdd(&store, "One too many", &id) == BTB_NOTES_FULL);
    CHECK(memcmp(&store, &copy, sizeof(store)) == 0 && id == 1234U);
    return 0;
}

static int TestMissing(void)
{
    BtbNoteStore store;
    BtbNote sentinel = {.id = 77U, .text = "unchanged"};
    BtbNote copy = sentinel;
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    CHECK(BtbNotesRead(&store, 55U, &sentinel) == BTB_NOTES_NOT_FOUND);
    CHECK(memcmp(&sentinel, &copy, sizeof(copy)) == 0);
    CHECK(BtbNotesAt(&store, 0U, &sentinel) == BTB_NOTES_NOT_FOUND);
    CHECK(memcmp(&sentinel, &copy, sizeof(copy)) == 0);
    return 0;
}

static int TestInvalid(void)
{
    BtbNoteStore store;
    BtbNoteStore copy;
    uint32_t id = 444U;
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    copy = store;
    CHECK(BtbNotesAdd(&store, "", &id) == BTB_NOTES_INVALID);
    CHECK(BtbNotesAdd(&store, NULL, &id) == BTB_NOTES_INVALID);
    CHECK(BtbNotesAdd(NULL, "Test", &id) == BTB_NOTES_INVALID);
    CHECK(BtbNotesUpdate(&store, 0U, "New") == BTB_NOTES_INVALID);
    CHECK(memcmp(&store, &copy, sizeof(store)) == 0 && id == 444U);
    return 0;
}

static int TestCopies(void)
{
    BtbNoteStore store;
    BtbNote note;
    uint32_t id;
    char input[] = "Review the build output";
    CHECK(BtbNotesInit(&store) == BTB_NOTES_OK);
    CHECK(BtbNotesAdd(&store, input, &id) == BTB_NOTES_OK);
    input[0] = 'X';
    CHECK(BtbNotesRead(&store, id, &note) == BTB_NOTES_OK);
    CHECK(strcmp(note.text, "Review the build output") == 0);
    note.text[0] = 'X';
    CHECK(BtbNotesRead(&store, id, &note) == BTB_NOTES_OK);
    CHECK(strcmp(note.text, "Review the build output") == 0);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) { fprintf(stderr, "Select one test case.\n"); return 2; }
    if (strcmp(argv[1], "add") == 0) return TestAdd();
    if (strcmp(argv[1], "update") == 0) return TestUpdate();
    if (strcmp(argv[1], "too-long") == 0) return TestTooLong();
    if (strcmp(argv[1], "capacity") == 0) return TestCapacity();
    if (strcmp(argv[1], "missing") == 0) return TestMissing();
    if (strcmp(argv[1], "invalid") == 0) return TestInvalid();
    if (strcmp(argv[1], "ownership") == 0) return TestCopies();
    fprintf(stderr, "Unknown test case: %s\n", argv[1]);
    return 2;
}
