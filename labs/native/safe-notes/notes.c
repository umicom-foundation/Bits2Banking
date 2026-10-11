/*-----------------------------------------------------------------------------
 * Bits to Banking — Safer C laboratory
 * File: labs/native/safe-notes/notes.c
 * PURPOSE: Implement a bounded, failure-atomic C23 text update.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <string.h>

UmicomNoteStatus UmicomNoteSet(UmicomNote *note, const char *text, size_t length)
{
    if (note == NULL || text == NULL) return UMICOM_NOTE_INVALID_INPUT;
    if (length >= sizeof(note->bytes)) return UMICOM_NOTE_TOO_LONG;
    /* Inputs must not overlap destination storage. `memmove` also tolerates
     * callers explicitly reusing note->bytes as input for a shorter edit. */
    memmove(note->bytes, text, length);
    note->bytes[length] = '\0';
    note->length = length;
    return UMICOM_NOTE_OK;
}
