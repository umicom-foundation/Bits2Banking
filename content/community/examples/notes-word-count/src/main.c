/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/community/examples/notes-word-count/src/main.c
 *
 * PURPOSE:
 *   Display a result from the shared notes component.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "note_words.h"
#include <stdio.h>

int main(void)
{
    const char *greeting = "Welcome to Umicom learning.";
    printf("Words: %zu\n", note_word_count(greeting));
    return 0;
}
