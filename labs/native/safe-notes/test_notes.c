/*-----------------------------------------------------------------------------
 * Bits to Banking — Safer C laboratory
 * File: labs/native/safe-notes/test_notes.c
 * PURPOSE: Check empty, ordinary, excessive and null-input updates.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <assert.h>
#include <string.h>

int main(void)
{
    UmicomNote note = {{0}, 0U};
    const char start[] = "Draft one";
    assert(UmicomNoteSet(&note, start, strlen(start)) == UMICOM_NOTE_OK);
    assert(note.length == 9U);
    assert(strcmp(note.bytes, start) == 0);

    char oversized[UMICOM_NOTE_CAPACITY + 2U];
    memset(oversized, 'x', sizeof(oversized));
    assert(UmicomNoteSet(&note, oversized, sizeof(oversized)) == UMICOM_NOTE_TOO_LONG);
    assert(note.length == 9U && strcmp(note.bytes, start) == 0);

    assert(UmicomNoteSet(&note, NULL, 0U) == UMICOM_NOTE_INVALID_INPUT);
    assert(UmicomNoteSet(NULL, start, strlen(start)) == UMICOM_NOTE_INVALID_INPUT);
    assert(UmicomNoteSet(&note, "", 0U) == UMICOM_NOTE_OK);
    assert(note.length == 0U && note.bytes[0] == '\0');
    return 0;
}
