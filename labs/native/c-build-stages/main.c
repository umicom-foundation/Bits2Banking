/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-build-stages/main.c
 *
 * PURPOSE:
 *   Expose preprocessing, object generation and linking with an actual Umicom C consumer.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "runner.h"
#include <inttypes.h>
#include <stdio.h>

#ifndef LESSON_FACTOR
#define LESSON_FACTOR 6
#endif
#define LESSON_STRING_INNER(value) #value
#define LESSON_STRING(value) LESSON_STRING_INNER(value)

int main(void)
{
    const char source[] = "int main(void) { return " LESSON_STRING(LESSON_FACTOR) " * 7; }";
    int32_t value = 0;
    if (!LessonEvaluate(source, sizeof(source) - 1U, &value)) {
        (void)fputs("The embedded source could not be evaluated.\n", stderr);
        return 1;
    }
    if (printf("Value: %" PRId32 "\n", value) < 0 || fflush(stdout) == EOF) return 1;
    return 0;
}
