/*-----------------------------------------------------------------------------
 * Bits2Banking
 * File: labs/native/compiler-inspection/main.c
 *
 * PURPOSE:
 *   Embed the Umicom C compiler and inspect a program before an optional bounded execution.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <umicom_c/umicom_c.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "--run") != 0)) {
        fputs("Usage: compiler-inspection [--run]\n", stderr);
        return 2;
    }
    static const char source[] = "int main(void) { return -(2 + 3 * 4); }";
    UmcInstruction program[UMC_PROGRAM_LIMIT];
    size_t count = 0U;
    UmcDiagnostic diagnostic;
    UmcStatus status = umc_compile(source, sizeof(source) - 1U,
        program, UMC_PROGRAM_LIMIT, &count, &diagnostic);
    if (status != UMC_OK) {
        fprintf(stderr, "Compile failed: %s\n", diagnostic.message);
        return 1;
    }
    UmcProgramInfo info;
    status = umc_inspect(program, count, &info, &diagnostic);
    if (status != UMC_OK) {
        fprintf(stderr, "Inspect failed: %s\n", diagnostic.message);
        return 1;
    }
    printf("Instructions: %zu\nPeak stack values: %zu\nEncoded bytes: %zu\n",
        info.instruction_count, info.peak_stack, info.bytecode_size);
    if (argc == 1) {
        puts("Ready for review; no program instructions have been executed.");
        return 0;
    }
    /* The caller selects the budget. The library still performs its complete
     * checks, because earlier inspection does not make a later call trusted. */
    UmcResult result;
    status = umc_execute(program, count, info.instruction_count, &result, &diagnostic);
    if (status != UMC_OK) {
        fprintf(stderr, "Execution failed: %s\n", diagnostic.message);
        return 1;
    }
    printf("Result: %" PRId32 "\n", result.value);
    return 0;
}
