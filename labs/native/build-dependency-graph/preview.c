/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/build-dependency-graph/preview.c
 *
 * PURPOSE:
 *   Show a bounded note through the shared Notes lab and an explicitly generated build setting.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include "lesson_config.h"
#include <stdio.h>

int main(void)
{
    UmicomNote note = {{0}, 0U};
    const char title[] = "Trace a build dependency";
    /* Reuse the teaching library rather than duplicate its bounds checks. */
    if (UmicomNoteSet(&note, title, sizeof(title) - 1U) != UMICOM_NOTE_OK) {
        fputs("Could not prepare the note.\n", stderr);
        return 1;
    }
#if LESSON_SHOW_HEADING
    if (puts("Umicom Notes preview") == EOF) return 1;
#endif
    if (fwrite(note.bytes, 1U, note.length, stdout) != note.length) return 1;
    return putchar('\n') == EOF ? 1 : 0;
}
