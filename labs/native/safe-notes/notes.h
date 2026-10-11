/*-----------------------------------------------------------------------------
 * Bits to Banking — Safer C laboratory
 * File: labs/native/safe-notes/notes.h
 * PURPOSE: Define an explicit, bounded Notes record and result contract.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#ifndef BITS_TO_BANKING_NOTES_H
#define BITS_TO_BANKING_NOTES_H
#include <stddef.h>

#define UMICOM_NOTE_CAPACITY 128U

typedef struct UmicomNote {
    char bytes[UMICOM_NOTE_CAPACITY];
    size_t length;
} UmicomNote;

typedef enum UmicomNoteStatus {
    UMICOM_NOTE_OK = 0,
    UMICOM_NOTE_INVALID_INPUT = 1,
    UMICOM_NOTE_TOO_LONG = 2
} UmicomNoteStatus;

/* The caller owns note and text. Never retain an input pointer.
 * On failure the original note remains unchanged. */
UmicomNoteStatus UmicomNoteSet(UmicomNote *note, const char *text, size_t length);

#endif
