/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-experiments/test_arithmetic.c
 *
 * PURPOSE:
 *   Verify precedence, signed arithmetic refusals and preserved results after execution failure.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <umicom_c/umicom_c.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const struct { const char *source; UmcStatus expected; int32_t value; } cases[] = {
        {"int main(void) { return 2 + 3 * 4; }", UMC_OK, 14},
        {"int main(void) { return (2 + 3) * 4; }", UMC_OK, 20},
        {"int main(void) { return 10 - 3 - 2; }", UMC_OK, 5},
        {"int main(void) { return 20 / 2 / 2; }", UMC_OK, 5},
        {"int main(void) { return -7 / 2; }", UMC_OK, -3},
        {"int main(void) { return -2147483647 - 1; }", UMC_OK, INT32_MIN},
        {"int main(void) { return 2147483647 + 1; }", UMC_ARITHMETIC_ERROR, 0},
        {"int main(void) { return 8 / (2 - 2); }", UMC_ARITHMETIC_ERROR, 0},
        {"int main(void) { return (-2147483647 - 1) / -1; }", UMC_ARITHMETIC_ERROR, 0},
        {"int main(void) { return -(-2147483647 - 1); }", UMC_ARITHMETIC_ERROR, 0}
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        UmcInstruction program[UMC_PROGRAM_LIMIT];
        size_t count = 0;
        if (umc_compile(cases[i].source, strlen(cases[i].source),
                program, UMC_PROGRAM_LIMIT, &count, NULL) != UMC_OK) return 1;
        UmcResult result = {123, 456};
        const UmcStatus status = umc_execute(program, count, count, &result, NULL);
        if (status != cases[i].expected ||
            (status == UMC_OK && (result.value != cases[i].value || result.instructions_executed != count)) ||
            (status != UMC_OK && (result.value != 123 || result.instructions_executed != 456))) {
            (void)fprintf(stderr, "Arithmetic case %zu failed its contract.\n", i);
            return 1;
        }
    }
    return 0;
}

