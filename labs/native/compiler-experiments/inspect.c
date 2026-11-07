/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-experiments/inspect.c
 *
 * PURPOSE:
 *   Display compiled instructions before executing one bounded arithmetic source argument.
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
    if (argc != 2) {
        (void)fputs("Supply one quoted source program: int main(void) { return 2 + 3 * 4; }\n", stderr);
        return 2;
    }
    UmcInstruction program[UMC_PROGRAM_LIMIT];
    UmcDiagnostic diagnostic = {0};
    size_t count = 0;
    const UmcStatus compiled = umc_compile(argv[1], strlen(argv[1]),
        program, UMC_PROGRAM_LIMIT, &count, &diagnostic);
    if (compiled != UMC_OK) {
        (void)fprintf(stderr, "Compile: %s at byte %zu, line %zu, column %zu\n",
            umc_status_text(compiled), diagnostic.source_offset,
            diagnostic.line, diagnostic.column);
        return 1;
    }
    /* The count becomes usable only after a successful compile. Partial output
       after rejection must never be treated as an executable program. */
    for (size_t i = 0; i < count; ++i) {
        if (printf("%zu: %s operand=%" PRId32 " source=%zu\n", i,
                umc_opcode_text(program[i].opcode), program[i].operand,
                program[i].source_offset) < 0) return 1;
    }
    UmcResult result = {0};
    const UmcStatus executed = umc_execute(program, count, count, &result, &diagnostic);
    if (executed != UMC_OK) {
        (void)fprintf(stderr, "Execute: %s at byte %zu\n",
            umc_status_text(executed), diagnostic.source_offset);
        return 1;
    }
    if (printf("Result: %" PRId32 "; instructions: %zu\n",
            result.value, result.instructions_executed) < 0 || fflush(stdout) == EOF) return 1;
    return 0;
}

