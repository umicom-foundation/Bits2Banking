/*-----------------------------------------------------------------------------
 * Bits to Banking — Safer C laboratory
 * File: labs/native/safe-notes/main.c
 * PURPOSE: Show a useful note with an explicit capacity and status result.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    UmicomNote note = {{0}, 0U};
    const char text[] = "Plan the Umicom Framework lesson";
    if (UmicomNoteSet(&note, text, strlen(text)) != UMICOM_NOTE_OK) {
        fputs("Could not save the note in memory.\n", stderr);
        return 1;
    }
    printf("Note (%zu bytes): %s\n", note.length, note.bytes);
    return 0;
}
