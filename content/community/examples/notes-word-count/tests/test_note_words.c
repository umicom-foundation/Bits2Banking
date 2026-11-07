/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/community/examples/notes-word-count/tests/test_note_words.c
 *
 * PURPOSE:
 *   Exercise empty, borrowed and whitespace-delimited text at the component boundary.
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
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const struct { const char *input; size_t expected; } cases[] = {
        {NULL, 0}, {"", 0}, {" \t\r\n\f\v", 0}, {"one", 1},
        {"  one  two\tthree\n", 3}, {"one\r\ntwo", 2},
        {"one,two", 1}, {"Welcome to Umicom learning.", 4}
    };
    for (size_t index = 0; index < sizeof(cases) / sizeof(cases[0]); ++index) {
        size_t actual = note_word_count(cases[index].input);
        if (actual != cases[index].expected) {
            fprintf(stderr, "Case %zu: expected %zu, got %zu\n",
                    index, cases[index].expected, actual);
            return EXIT_FAILURE;
        }
    }
    char borrowed[] = "Read this note";
    if (note_word_count(borrowed) != 3 || strcmp(borrowed, "Read this note") != 0) {
        fputs("Counting must preserve the caller text.\n", stderr);
        return EXIT_FAILURE;
    }
    puts("Word-count checks passed.");
    return EXIT_SUCCESS;
}
