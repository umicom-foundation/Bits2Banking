<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/fpml-for-treasury/03-check-terms-in-c.md

PURPOSE:
Keep amounts and basis points exact at the native boundary and trace rejects without overwriting the result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Check the Mapped Terms in C23

[Course contents](index.md) · [Previous lesson · Read and Validate the Import Boundary](02-read-the-import-boundary.md)

Keep amounts and basis points exact at the native boundary and trace rejects without overwriting the result.

## Set the practice limits

This first validation function receives integers from a hypothetical version-aware adapter. Use 10,000,000 cents for the USD 100,000 notional and 425 basis points for the rate. The classroom upper limits are USD 1,000,000 and 50.00 percent. Use no floating-point conversion and keep the candidate out of accepted storage when a check fails.

~~~c
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct SwapTerms {
    int64_t notional_cents;
    unsigned fixed_payer;
    unsigned fixed_receiver;
    unsigned floating_payer;
    unsigned floating_receiver;
    unsigned fixed_basis_points;
    bool currency_is_usd;
};

static bool admit(struct SwapTerms candidate, struct SwapTerms *out)
{
    // Every check runs before writing the caller's accepted record.
    if (!candidate.currency_is_usd || candidate.notional_cents <= 0 ||
        candidate.notional_cents > INT64_C(100000000) ||
        candidate.fixed_basis_points > 5000u ||
        candidate.fixed_payer == 0 || candidate.fixed_receiver == 0 ||
        candidate.fixed_payer == candidate.fixed_receiver ||
        candidate.floating_payer != candidate.fixed_receiver ||
        candidate.floating_receiver != candidate.fixed_payer) {
        return false;
    }
    *out = candidate;
    return true;
}

int main(void)
{
    const struct SwapTerms cedar = {10000000, 1, 2, 2, 1, 425, true};
    struct SwapTerms accepted = {0};
    struct SwapTerms wrong_direction = cedar;
    wrong_direction.floating_payer = 1;
    assert(admit(cedar, &accepted));
    assert(!admit(wrong_direction, &accepted));
    assert(accepted.notional_cents == 10000000 && accepted.fixed_basis_points == 425);
    assert(accepted.floating_payer == 2 && accepted.floating_receiver == 1);
    puts("accepted: TRN-401, rejected: leg direction error");
    return 0;
}
~~~

1. Copy the C code into swap_terms.c in a practice folder. Keep the assert checks enabled.
2. With a suitable compiler, build with the command below. The program expects no input.
3. Check the line printed on success. Change the candidate rate to 5001 and predict which assertion would stop if cedar were changed. For a clean rejection test, change only wrong_direction and add a separate rejected candidate.

~~~text
cc -std=c23 -Wall -Wextra -pedantic swap_terms.c -o swap-terms
./swap-terms
Expected: accepted: TRN-401, rejected: leg direction error
~~~

On Windows with a C23 GCC toolchain, choose swap-terms.exe after -o and run .\swap-terms.exe in PowerShell. If the compiler does not recognize -std=c23, use the pencil trace while you check which compiler your environment provides.

## Compare the rate limit in D

D uint holds an unsigned integer. This slice exercises the same training bound. A D unit test can check both sides of the boundary without involving the XML adapter.

~~~d
bool withinTrainingRate(uint basisPoints) {
    return basisPoints <= 5_000;
}

unittest {
    assert(withinTrainingRate(5_000));
    assert(!withinTrainingRate(5_001));
}
~~~

- [D keyword reference](../../../courses/d-keyword-reference/index.html)
- [C23 keyword reference](../../../courses/c23-keyword-reference/index.html)

[Browser edition](../../../courses/fpml-for-treasury/lessons/03-check-terms-in-c.html)

