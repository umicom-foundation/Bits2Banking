/*-----------------------------------------------------------------------------
 * Bits to Banking | Umicom Foundation
 * File: labs/native/contributor-notes/main.c
 * PURPOSE: First native Umicom Notes teaching programme — real build and tests.
 * AUTHOR: Sammy Hegab | LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>

int main(void)
{
    BtbNoteStore store;
    uint32_t firstId = 0U;
    uint32_t secondId = 0U;
    BtbNote note;
    if (BtbNotesInit(&store) != BTB_NOTES_OK) return 1;
    if (BtbNotesAdd(&store, "Check Git status before adding files", &firstId) != BTB_NOTES_OK)
        return 2;
    if (BtbNotesAdd(&store, "Run CMake, then CTest", &secondId) != BTB_NOTES_OK)
        return 3;
    if (BtbNotesUpdate(&store, firstId,
                       "Check Git status and staged changes before committing") != BTB_NOTES_OK)
        return 4;
    puts("Umicom Notes — first C23 programme (temporary in-memory data)");
    for (size_t index = 0U; index < BtbNotesCount(&store); ++index) {
        if (BtbNotesAt(&store, index, &note) != BTB_NOTES_OK) return 5;
        printf("%u. %s\n", (unsigned)note.id, note.text);
    }
    return secondId == 2U ? 0 : 6;
}
