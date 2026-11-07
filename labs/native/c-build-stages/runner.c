/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/c-build-stages/runner.c
 *
 * PURPOSE:
 *   Keep the teaching executable thin by delegating language processing to Umicom C.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "runner.h"
#include <umicom_c/umicom_c.h>

int LessonEvaluate(const char *source, size_t length, int32_t *value)
{
    if (source == NULL || value == NULL) return 0;
    UmcInstruction program[UMC_PROGRAM_LIMIT];
    UmcDiagnostic diagnostic = {0};
    size_t count = 0;
    if (umc_compile(source, length, program, UMC_PROGRAM_LIMIT,
            &count, &diagnostic) != UMC_OK) return 0;
    UmcResult result = {0};
    /* This language has no jumps. One instruction budget per instruction is
       enough; only the compiler's successful count is permitted to execute. */
    if (umc_execute(program, count, count, &result, &diagnostic) != UMC_OK) return 0;
    *value = result.value;
    return 1;
}
