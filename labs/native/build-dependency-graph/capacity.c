/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/build-dependency-graph/capacity.c
 *
 * PURPOSE:
 *   Inspect the public Notes record without depending on preview-only build settings.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "notes.h"
#include <stdio.h>

int main(void)
{
    /* sizeof measures the array storage. Reserve a byte for its terminator. */
    UmicomNote note = {{0}, 0U};
    printf("Storage bytes: %zu\nMaximum text bytes: %zu\n",
        sizeof(note.bytes), sizeof(note.bytes) - 1U);
    return ferror(stdout) ? 1 : 0;
}
