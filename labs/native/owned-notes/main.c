/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/owned-notes/main.c
 * PURPOSE: Keep a small educational Notes journal in owned memory.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    BtbNoteStore *store = NULL;
    BtbNoteId id = 0U;
    if (BtbNoteStoreCreate(&store) != BTB_NOTE_OK) return EXIT_FAILURE;
    BtbNoteStatus status = BtbNoteStoreAdd(
        store, "Umicom contributor tasks",
        "Review the Notes example, write one test, then submit a pull request.", &id);
    if (status == BTB_NOTE_OK) {
        char title[BTB_NOTES_MAX_TITLE_BYTES + 1U];
        char body[BTB_NOTES_MAX_BODY_BYTES + 1U];
        status = BtbNoteStoreRead(store, id, title, sizeof(title), body, sizeof(body));
        if (status == BTB_NOTE_OK)
            (void)printf("Note %u\n%s\n%s\n", (unsigned)id, title, body);
    }
    if (status != BTB_NOTE_OK)
        (void)fprintf(stderr, "Notes demonstration failed: %s\n", BtbNoteStatusText(status));
    BtbNoteStoreDestroy(store);
    return status == BTB_NOTE_OK ? EXIT_SUCCESS : EXIT_FAILURE;
}
