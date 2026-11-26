/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/umicom-c-brew-time/brew-time-sdk.c
 *
 * PURPOSE:
 * Check compilation, execution and caller-owned output in a C23 client.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <inttypes.h>
#include <stdio.h>
#include <umicom_c/umicom_c.h>

int main(void)
{
    const char source[] = "int main(void) { return (4 * 60) + 15; }";
    const char incomplete[] = "int main(void) { return (4 * ) + 15; }";
    UmcInstruction program[32];
    UmcDiagnostic diagnostic = {0};
    UmcResult result = {0};
    size_t count = 0;

    /* Confirm the invalid input never produces a usable instruction count. */
    if (umc_compile(incomplete, sizeof incomplete - 1U, program,
            sizeof program / sizeof program[0], &count, &diagnostic) == UMC_OK || count != 0U) {
        fputs("Incomplete source produced a usable program.\n", stderr);
        return 1;
    }

    /* Only use instruction storage after the compiler reports success. */
    if (umc_compile(source, sizeof source - 1U, program,
            sizeof program / sizeof program[0], &count, &diagnostic) != UMC_OK || count != 6U) {
        fputs("The practice recipe did not compile to six instructions.\n", stderr);
        return 1;
    }
    if (umc_execute(program, count, 64U, &result, &diagnostic) != UMC_OK || result.value != 255) {
        fputs("The practice recipe did not return 255 seconds.\n", stderr);
        return 1;
    }

    /* Give the second run too little fuel. The caller still owns the earlier
       value, and the failed status keeps it from being treated as a new result. */
    if (umc_execute(program, count, 1U, &result, &diagnostic) == UMC_OK || result.value != 255) {
        fputs("The refused execution did not preserve the previous value.\n", stderr);
        return 1;
    }
    printf("Verified a completed result of %" PRId32 " seconds and preserved it on refusal.\n", result.value);
    return 0;
}
