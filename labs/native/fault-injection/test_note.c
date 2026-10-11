/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/fault-injection/test_note.c
 * PURPOSE: Force every allocation boundary and verify failure atomicity.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "note.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct Faults {
    size_t attempts;
    size_t failOn;
    size_t live;
} Faults;

static void *TryAllocate(size_t size, void *context)
{
    Faults *faults = context;
    ++faults->attempts;
    if (faults->attempts == faults->failOn) return NULL;
    void *pointer = malloc(size);
    if (pointer != NULL) ++faults->live;
    return pointer;
}

static void TryRelease(void *pointer, void *context)
{
    Faults *faults = context;
    if (pointer != NULL) {
        if (faults->live == 0U) abort();
        --faults->live;
        free(pointer);
    }
}

#define CHECK(condition) do { \
    if (!(condition)) { \
        fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
        return EXIT_FAILURE; \
    } \
} while (0)

int main(void)
{
    const char firstTitle[] = "Build Umicom Notes";
    const char firstBody[] = "Review document ownership.";
    const char replacement[] = "Write C23 tests";
    const char newBody[] = "Make every allocation fail once.";
    Faults faults = {0};
    BtbAllocator allocator = {TryAllocate, TryRelease, &faults};
    BtbNote note = {0};

    faults.failOn = 1U;
    CHECK(BtbNoteInit(&note, allocator, firstTitle, strlen(firstTitle),
                      firstBody, strlen(firstBody)) == BTB_NO_MEMORY);
    CHECK(faults.live == 0U && BtbNoteRevision(&note) == 0U);

    faults.failOn = faults.attempts + 2U;
    CHECK(BtbNoteInit(&note, allocator, firstTitle, strlen(firstTitle),
                      firstBody, strlen(firstBody)) == BTB_NO_MEMORY);
    CHECK(faults.live == 0U && BtbNoteTitle(&note) == NULL);

    faults.failOn = 0U;
    CHECK(BtbNoteInit(&note, allocator, firstTitle, strlen(firstTitle),
                      firstBody, strlen(firstBody)) == BTB_OK);
    CHECK(faults.live == 2U && BtbNoteRevision(&note) == 1U);
    CHECK(strcmp(BtbNoteBody(&note), firstBody) == 0);

    CHECK(BtbNoteReplace(&note, 0U, replacement, strlen(replacement),
                         newBody, strlen(newBody)) == BTB_CONFLICT);
    CHECK(faults.live == 2U && BtbNoteRevision(&note) == 1U);

    for (size_t failIndex = 1U; failIndex <= 2U; ++failIndex) {
        faults.failOn = faults.attempts + failIndex;
        CHECK(BtbNoteReplace(&note, 1U, replacement, strlen(replacement),
                             newBody, strlen(newBody)) == BTB_NO_MEMORY);
        CHECK(faults.live == 2U && BtbNoteRevision(&note) == 1U);
        CHECK(strcmp(BtbNoteTitle(&note), firstTitle) == 0);
        CHECK(strcmp(BtbNoteBody(&note), firstBody) == 0);
    }

    faults.failOn = 0U;
    CHECK(BtbNoteReplace(&note, 1U, replacement, strlen(replacement),
                         newBody, strlen(newBody)) == BTB_OK);
    CHECK(BtbNoteRevision(&note) == 2U && faults.live == 2U);
    CHECK(strcmp(BtbNoteTitle(&note), replacement) == 0);
    CHECK(strcmp(BtbNoteBody(&note), newBody) == 0);

    /* Rejected embedded-NUL input must not request memory or change state. */
    const char bad[] = {'N', 'O', '\0', 'T', 'E'};
    size_t before = faults.attempts;
    CHECK(BtbNoteReplace(&note, 2U, bad, sizeof bad,
                         newBody, strlen(newBody)) == BTB_INVALID);
    CHECK(faults.attempts == before && BtbNoteRevision(&note) == 2U);

    CHECK(BtbNoteReplace(&note, 2U, newBody, BTB_MAX_TEXT_BYTES + 1U,
                         newBody, strlen(newBody)) == BTB_LIMIT);
    CHECK(faults.attempts == before);

    BtbNoteDestroy(&note);
    CHECK(faults.live == 0U && BtbNoteRevision(&note) == 0U);
    BtbNoteDestroy(&note); /* Repeat destruction is harmless. */
    CHECK(faults.live == 0U);
    puts("Allocation-failure and ownership tests passed.");
    return EXIT_SUCCESS;
}
