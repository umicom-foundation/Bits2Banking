<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/44-add-with-a-checked-result.md

PURPOSE:
Add with a checked result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Add with a checked result

A calculator can keep adding digits. A C integer has a finite range. Overflow means the result cannot be represented in the type you chose. Use a checked operation before handing the result to another part of your program.

## Read the meaning of the return value

`ckd_add(&candidate, left, right)` attempts the mathematical sum. It returns `false` when the sum fits in the type of `candidate`. It returns `true` when the sum is outside that range. The macro writes a wrapped value into `candidate` in that case; the example discards it. The wrapper `add_int` returns `true` on success because it reports whether the application should use the result. Follow the two names when reading the branches.

## Preserve the last valid value

A **candidate** is temporary storage for a result you are still checking. The output `*result` belongs to the caller. Copy the candidate after success. `INT_MAX` is the greatest `int` on the selected compiler. Adding one to it cannot fit. A previous answer of 42 should remain available when a new sum is refused.

## Connect to Umicom

Use this pattern when an Umicom application accumulates counts for display. A shared Framework service owns the arithmetic and outcome. The display keeps its last valid count and reports refusal. In exercise code, boundary tests make that contract visible without launching an application.

## Trace the logic

~~~text
TRY ADD left AND right INTO temporary
IF THE SUM DOES NOT FIT
    REPORT REFUSAL
OTHERWISE
    COPY temporary TO the caller
    REPORT SUCCESS
~~~

~~~c
static bool add_int(int left, int right, int *result)
{
    /* The macro may write a wrapped value even when it reports overflow. */
    int candidate;
    if (ckd_add(&candidate, left, right)) return false;
    *result = candidate;
    return true;
}
~~~

## Build and run one practice case

1. Open a PowerShell terminal with GCC, CMake and Ninja on the search path. To use Clang, select `clang` in the configure command and choose a separate build directory in all three commands. Check that the selected C compiler and its headers provide `<stdckdint.h>`. If that header is missing, the final lesson demonstrates `size_t` guards using only older headers.
2. Open `labs/native/checked-integers/add.c`. Read the successful case and at least one refusal case.
3. Run the commands one at a time. Stop on the first error so an earlier executable cannot be mistaken for the latest build.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/native/checked-integers -B build/checked-integers -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build/checked-integers --target checked-integers-add
ctest --test-dir build/checked-integers -R "^lesson[.]checked-integers[.]add$" -V --no-tests=error
~~~

Expect one passing test and this line of program output.

~~~text
The total is 42. The refused sum kept it unchanged.
~~~

## Try a change

Change `(19, 23)` to `(20, 23)` and predict which case fails. Update the expected sum and the initial valid value deliberately. Keep the `INT_MAX + 1` overflow case as two separate macro arguments; do not use a regular overflowing expression.

## If a result differs

If exact-limit addition fails, compare the type of the temporary with the type of the output. If the old value changed on refusal, check whether the macro received the caller’s address instead of the temporary address.

## Read the C language reference

[WG14 N3220, section 7.20.1 on checked integer operations](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=326)

[Course contents](index.md) · [Previous: Admit resource labels without trusting their contents](43-admit-resource-labels-without-trusting-content.md) · [Next: Separate subtraction from a debit rule](45-separate-subtraction-from-a-debit-rule.md)
