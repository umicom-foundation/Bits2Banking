<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/45-separate-subtraction-from-a-debit-rule.md

PURPOSE:
Separate subtraction from a debit rule

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate subtraction from a debit rule

You hold three practice tokens and someone asks for five. The number −2 is a valid result on paper. A policy can still forbid that transaction.

## Choose a destination before interpreting the status

The mathematical operation is 3 minus 5. The checked macro accepts −2 in a signed `int`. It reports failure for the same numbers when the destination is `unsigned`. The macro still writes the wrapped unsigned value. The program checks it only to explain the language rule and never treats it as available tokens.

## Apply the account rule explicitly

The practice account declines a negative requested debit and any amount above the balance. An exact debit of the whole balance succeeds with a result of zero. This domain rule belongs to the account and applies regardless of the machine integer limit. Real account records also need an explicit monetary unit and transaction policy.

## Connect to Umicom

A banking interface can display “insufficient practice balance” after domain refusal and a different message after arithmetic refusal. Carry those outcomes through the Framework service. The lesson changes only local variables and connects to no banking system.

## Trace the logic

~~~text
IF debit IS NEGATIVE OR debit EXCEEDS balance
    REFUSE THE PRACTICE DEBIT
OTHERWISE
    SUBTRACT debit FROM balance WITH A RANGE CHECK
    SAVE ONLY A VALID RESULT
~~~

~~~c
static bool reserve_units(int balance, int debit, int *remaining)
{
    /* This practice account does not permit overdrafts or negative debits. */
    if (debit < 0 || balance < debit) return false;
    int candidate;
    if (ckd_sub(&candidate, balance, debit)) return false;
    *remaining = candidate;
    return true;
}
~~~

## Build and run one practice case

1. Open a PowerShell terminal with GCC, CMake and Ninja on the search path. To use Clang, select `clang` in the configure command and choose a separate build directory in all three commands. Check that the selected C compiler and its headers provide `<stdckdint.h>`. If that header is missing, the final lesson demonstrates `size_t` guards using only older headers.
2. Open `labs/native/checked-integers/subtract.c`. Read the successful case and at least one refusal case.
3. Run the commands one at a time. Stop on the first error so an earlier executable cannot be mistaken for the latest build.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/native/checked-integers -B build/checked-integers -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build/checked-integers --target checked-integers-subtract
ctest --test-dir build/checked-integers -R "^lesson[.]checked-integers[.]subtract$" -V --no-tests=error
~~~

Expect one passing test and this line of program output.

~~~text
Signed difference: -2. The practice account refused the overdraft.
~~~

## Try a change

Add cases for a zero debit and a debit equal to the balance. Before running them, write down the correct post-operation balance and whether the call should succeed.

## If a result differs

If a refused debit reports a huge positive balance, look for conversion to `unsigned` before the policy check or an output written from the failed macro result.

## Read the C language reference

[WG14 N3220, section 7.20.1 on checked integer operations](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=326)

[Course contents](index.md) · [Previous: Add with a checked result](44-add-with-a-checked-result.md) · [Next: Check block counts before using bytes](46-check-block-counts-before-using-bytes.md)
