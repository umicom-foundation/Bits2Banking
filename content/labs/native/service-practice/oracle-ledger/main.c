/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: content/labs/native/service-practice/oracle-ledger/main.c
 *
 * PURPOSE:
 *   Keep absence and numeric zero distinct when decoding a training Oracle projection.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct OptionalAmount {
    bool present;
    int64_t cents;
};

/* The caller supplies only values from successful, range-checked fetches. */
static bool decode_amount(int16_t indicator, int64_t value, struct OptionalAmount *amount)
{
    if (indicator == -1) {
        *amount = (struct OptionalAmount){.present = false, .cents = 0};
        return true;
    }
    if (indicator != 0) {
        // Unrecognised and truncation indicators cannot replace a complete amount.
        return false;
    }
    *amount = (struct OptionalAmount){.present = true, .cents = value};
    return true;
}

int main(void)
{
    struct OptionalAmount amount = {.present = false, .cents = 0};
    if (!decode_amount(0, 0, &amount) || !amount.present || amount.cents != 0 ||
        !decode_amount(-1, 12345, &amount) || amount.present ||
        !decode_amount(0, -850, &amount) || !amount.present || amount.cents != -850 ||
        decode_amount(-2, 1, &amount) || !amount.present || amount.cents != -850) {
        fputs("amount decoding mismatch\n", stderr);
        return 1;
    }
    puts("null, zero and refusal checks ready");
    return 0;
}
