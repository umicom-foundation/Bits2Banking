/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/community/examples/notes-word-count/src/note_words.c
 *
 * PURPOSE:
 *   Count words once for both the console caller and regression checks.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "note_words.h"
#include <stdbool.h>

static bool is_separator(char value)
{
    return value == ' ' || value == '\t' || value == '\n' ||
           value == '\r' || value == '\f' || value == '\v';
}

size_t note_word_count(const char *text)
{
    size_t count = 0;
    bool inside_word = false;
    if (text == NULL) return 0;
    /* A transition from separator to content begins one word. The caller
     * owns the string throughout; no allocation or mutation is necessary. */
    for (const char *cursor = text; *cursor != '\0'; ++cursor) {
        if (is_separator(*cursor)) {
            inside_word = false;
        } else if (!inside_word) {
            ++count;
            inside_word = true;
        }
    }
    return count;
}
