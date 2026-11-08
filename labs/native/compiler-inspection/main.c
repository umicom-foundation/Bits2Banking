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
#include <umicom_c/trace.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    /* Keep the existing review and run modes. Tracing is another explicit
     * execution choice and delegates stack behaviour to the shared runtime. */
#if 0
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "--run") != 0)) {
        fputs("Usage: compiler-inspection [--run]\n", stderr);
        return 2;
    }
#endif
    /* Retain the arithmetic-only admission and fixture. An explicit profile
     * selector reuses the same compiler, inspection and execution ownership. */
#if 0
    if (argc > 2 || (argc == 2 && strcmp(argv[1], "--run") != 0 && strcmp(argv[1], "--trace") != 0)) {
        fputs("Usage: compiler-inspection [--run|--trace]\n", stderr);
        return 2;
    }
    static const char source[] = "int main(void) { return -(2 + 3 * 4); }";
#endif
    const int comparison = argc > 1 && strcmp(argv[1], "--comparison") == 0;
    const int mode_index = comparison ? 2 : 1;
    if (argc > mode_index + 1 || (argc == mode_index + 1 &&
        strcmp(argv[mode_index], "--run") != 0 && strcmp(argv[mode_index], "--trace") != 0)) {
        fputs("Usage: compiler-inspection [--comparison] [--run|--trace]\n", stderr);
        return 2;
    }
    const char *source = comparison ? "int main(void) { return 2 + 3 < 2 * 3; }" :
        "int main(void) { return -(2 + 3 * 4); }";
    UmcInstruction program[UMC_PROGRAM_LIMIT];
    size_t count = 0U;
    UmcDiagnostic diagnostic;
    /* Source is now a selected borrowed string; retain the array-only length
     * expression for review and measure the selected string explicitly. */
#if 0
    UmcStatus status = umc_compile(source, sizeof(source) - 1U,
#endif
    UmcStatus status = umc_compile(source, strlen(source),
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
    /* Review remains the default for either profile. Earlier arity is retained. */
#if 0
    if (argc == 1) {
#endif
    if (argc == mode_index) {
        puts("Ready for review; no program instructions have been executed.");
        return 0;
    }
    /* The caller selects the budget. The library still performs its complete
     * checks, because earlier inspection does not make a later call trusted. */
    UmcResult result;
    /* The previous call is retained below. The ordinary path remains available;
     * the trace path owns storage and reads only the count the runtime publishes. */
#if 0
    status = umc_execute(program, count, info.instruction_count, &result, &diagnostic);
#endif
    /* The mode follows the optional profile selector; retain the old offset. */
#if 0
    if (strcmp(argv[1], "--trace") == 0) {
#endif
    if (strcmp(argv[mode_index], "--trace") == 0) {
        UmcTraceStep steps[UMC_PROGRAM_LIMIT];
        size_t used = 0U;
        status = umc_execute_trace(program, count, info.instruction_count, &result,
            steps, UMC_PROGRAM_LIMIT, &used, &diagnostic);
        for (size_t i = 0U; i < used; ++i) {
            printf("%zu %s depth=%zu top=%" PRId32 " status=%s\n",
                steps[i].instruction_index, umc_opcode_text(steps[i].opcode),
                steps[i].stack_depth, steps[i].top, umc_status_text(steps[i].status));
        }
    } else {
        status = umc_execute(program, count, info.instruction_count, &result, &diagnostic);
    }
    if (status != UMC_OK) {
        fprintf(stderr, "Execution failed: %s\n", diagnostic.message);
        return 1;
    }
    printf("Result: %" PRId32 "\n", result.value);
    return 0;
}
