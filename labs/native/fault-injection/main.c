/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/fault-injection/main.c
 * PURPOSE: Demonstrate ordinary note creation with caller-owned allocator.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "note.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void *Allocate(size_t size, void *context) { (void)context; return malloc(size); }
static void Release(void *pointer, void *context) { (void)context; free(pointer); }

int main(void)
{
    BtbNote note = {0};
    const char title[] = "Review Framework documentation";
    const char body[] = "Prepare one contributor lesson.";
    BtbAllocator allocator = {Allocate, Release, NULL};
    if (BtbNoteInit(&note, allocator, title, strlen(title), body, strlen(body)) != BTB_OK) {
        fputs("Could not create a Notes record.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Note revision %llu\nTitle: %s\nText: %s\n",
           (unsigned long long)BtbNoteRevision(&note),
           BtbNoteTitle(&note), BtbNoteBody(&note));
    BtbNoteDestroy(&note);
    return EXIT_SUCCESS;
}
