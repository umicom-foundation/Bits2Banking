/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/native/compiler-experiments/test_validation.c
 *
 * PURPOSE:
 *   Reject malformed instruction shapes and demonstrate that RETURN consumes execution fuel.
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

int main(void)
{
    const UmcInstruction valid[] = {{UMC_PUSH, 7, 0}, {UMC_RETURN, 0, 0}};
    const UmcInstruction underflow[] = {{UMC_ADD, 0, 0}, {UMC_RETURN, 0, 0}};
    const UmcInstruction excess[] = {{UMC_PUSH, 1, 0}, {UMC_PUSH, 2, 0}, {UMC_RETURN, 0, 0}};
    const UmcInstruction trailing[] = {{UMC_PUSH, 1, 0}, {UMC_RETURN, 0, 0}, {UMC_PUSH, 2, 0}};
    const UmcInstruction operand[] = {{UMC_PUSH, 1, 0}, {UMC_RETURN, 9, 0}};
    const UmcInstruction unknown[] = {{(UmcOpcode)99, 0, 0}};
    const struct { const UmcInstruction *code; size_t count; } bad[] = {
        {underflow, 2}, {excess, 3}, {trailing, 3}, {operand, 2}, {unknown, 1}, {valid, 1}
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; ++i) {
        UmcResult result = {123, 456};
        if (umc_execute(bad[i].code, bad[i].count, 99, &result, NULL) != UMC_BAD_BYTECODE ||
                result.value != 123 || result.instructions_executed != 456) {
            (void)fprintf(stderr, "Validation case %zu failed.\n", i);
            return 1;
        }
    }
    for (size_t fuel = 0; fuel < 2; ++fuel) {
        UmcResult result = {123, 456};
        if (umc_execute(valid, 2, fuel, &result, NULL) != UMC_FUEL_EXHAUSTED ||
                result.value != 123 || result.instructions_executed != 456) return 1;
    }
    UmcResult result = {0};
    return umc_execute(valid, 2, 2, &result, NULL) == UMC_OK &&
        result.value == 7 && result.instructions_executed == 2 ? 0 : 1;
}

