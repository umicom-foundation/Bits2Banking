/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/community/examples/notes-word-count/include/note_words.h
 *
 * PURPOSE:
 *   Declare the shared word-counting contract for a small notes exercise.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_LEARNING_NOTE_WORDS_H
#define UMICOM_LEARNING_NOTE_WORDS_H

#include <stddef.h>

/* Read borrowed, zero-terminated text without modifying it. NULL counts as
 * empty. Only ASCII space, tab and line-ending characters separate words;
 * this exercise does not implement natural-language tokenisation. */
size_t note_word_count(const char *text);

#endif
