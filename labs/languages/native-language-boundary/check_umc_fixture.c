/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/check_umc_fixture.c
 *
 * PURPOSE:
 *   Qualify the language lessons' literal bytecode through the real Umicom C runtime and demonstrate envelope limits.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include "umicom_c/umicom_c.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "%d: %s\n", __LINE__, #x); return 1; } } while (0)
int main(void)
{
    const uint8_t fixture[26] = {
        0x55, 0x4d, 0x43, 0x42, 1, 0, 2, 0,
        1, 42, 0, 0, 0, 0, 0, 0, 0,
        7, 0, 0, 0, 0, 0, 0, 0, 0};
    UmcInstruction instructions[UMC_PROGRAM_LIMIT];
    UmcDiagnostic diagnostic = {0};
    UmcProgramInfo info = {0};
    UmcResult result = {0};
    size_t count = 0U;
    CHECK(umc_decode(fixture, sizeof fixture, instructions, UMC_PROGRAM_LIMIT, &count, &diagnostic) == UMC_OK);
    CHECK(count == 2U);
    CHECK(umc_inspect(instructions, count, &info, &diagnostic) == UMC_OK);
    CHECK(info.instruction_count == 2U && info.peak_stack == 1U && info.bytecode_size == 26U);
    CHECK(umc_execute(instructions, count, 2U, &result, &diagnostic) == UMC_OK && result.value == 42);
    for (size_t length = 0U; length < sizeof fixture; ++length) {
        count = 99U;
        CHECK(umc_decode(fixture, length, instructions, UMC_PROGRAM_LIMIT, &count, &diagnostic) != UMC_OK);
        CHECK(count == 0U);
    }
    /* The teaching header readers accept both variants below. Only the real
     * runtime inspects their bodies and rejects these stronger violations. */
    uint8_t damaged[sizeof fixture];
    memcpy(damaged, fixture, sizeof damaged); damaged[8] = 255U;
    CHECK(umc_decode(damaged, sizeof damaged, instructions, UMC_PROGRAM_LIMIT, &count, &diagnostic) != UMC_OK && count == 0U);
    memcpy(damaged, fixture, sizeof damaged); damaged[4] = 6U;
    CHECK(umc_decode(damaged, sizeof damaged, instructions, UMC_PROGRAM_LIMIT, &count, &diagnostic) == UMC_BAD_BYTECODE && count == 0U);
    puts("Umicom C runtime: literal fixture returns 42; invalid opcode and noncanonical profile refused");
    return fflush(stdout) == 0 ? 0 : 2;
}
