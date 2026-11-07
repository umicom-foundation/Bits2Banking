/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-experiments/test_grammar.c
 *
 * PURPOSE:
 *   Check grammar admission, literal limits and output-count publication through the public compiler API.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <umicom_c/umicom_c.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const struct { const char *source; UmcStatus expected; } cases[] = {
        {"int main(void) { return 2 + 3 * 4; }", UMC_OK},
        {"int main(void) { return (2 + 3) * 4; }", UMC_OK},
        {"int main(void) { return 2147483647; }", UMC_OK},
        {"int main(void) { return 2147483648; }", UMC_LITERAL_RANGE},
        {"int main(void) { return -2147483648; }", UMC_LITERAL_RANGE},
        {"int main(void) { return 2 + ; }", UMC_SYNTAX_ERROR},
        {"int main(void) { return 2; } extra", UMC_SYNTAX_ERROR},
        {"int main(void) { return 2; } /* open", UMC_SYNTAX_ERROR},
        {"int main(void) { return 2; } // closed by end", UMC_OK}
    };
    for (size_t i = 0; i < sizeof cases / sizeof cases[0]; ++i) {
        UmcInstruction program[UMC_PROGRAM_LIMIT];
        size_t count = 99;
        UmcDiagnostic diagnostic = {0};
        const UmcStatus actual = umc_compile(cases[i].source, strlen(cases[i].source),
            program, UMC_PROGRAM_LIMIT, &count, &diagnostic);
        if (actual != cases[i].expected || (actual != UMC_OK && count != 0)) {
            (void)fprintf(stderr, "Grammar case %zu: %s, count %zu\n",
                i, umc_status_text(actual), count);
            return 1;
        }
    }
    /* A source span need not have a terminating zero byte. The array contains
       an invalid trailing byte which is deliberately outside the admitted span. */
    const char source[] = "int main(void) { return 7; }?";
    UmcInstruction program[UMC_PROGRAM_LIMIT];
    size_t count = 0;
    if (umc_compile(source, sizeof source - 2, program, UMC_PROGRAM_LIMIT,
            &count, NULL) != UMC_OK) return 1;
    count = 99;
    if (umc_compile(source, sizeof source - 2, program, 1, &count, NULL)
            != UMC_PROGRAM_TOO_LARGE || count != 0) return 1;
    return 0;
}

