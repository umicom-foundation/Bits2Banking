/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-build-stages/test_runner.c
 *
 * PURPOSE:
 *   Check consumer output publication for accepted source, syntax errors and arithmetic rejection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "runner.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    const char good[] = "int main(void) { return 6 * 7; }";
    const char bad[] = "int main(void) { return 6 * ; }";
    const char divide[] = "int main(void) { return 6 / 0; }";
    int32_t value = -99;
    if (!LessonEvaluate(good, sizeof(good) - 1U, &value) || value != 42) return 1;
    value = -99;
    if (LessonEvaluate(bad, strlen(bad), &value) || value != -99) return 2;
    if (LessonEvaluate(divide, strlen(divide), &value) || value != -99) return 3;
    if (LessonEvaluate(NULL, 0, &value) || value != -99) return 4;
    if (LessonEvaluate(good, sizeof(good) - 1U, NULL)) return 5;
    (void)puts("Consumer boundary checks completed.");
    return 0;
}
