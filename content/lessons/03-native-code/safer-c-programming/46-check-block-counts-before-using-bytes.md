<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/46-check-block-counts-before-using-bytes.md

PURPOSE:
Check block counts before using bytes

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check block counts before using bytes

An image description may express a length in blocks, while memory planning needs bytes. A block is a fixed-sized portion of the teaching format. This example uses 512 bytes per block and calculates the requirement without allocating memory or accessing a drive.

## Count in the right unit

Eight blocks of 512 bytes occupy 4096 bytes. A count of blocks and a count of bytes both fit in `size_t` while representing different units. Give the variables names that show which quantity each holds.

## Check the edge

`SIZE_MAX` is the largest value representable by `size_t`. Dividing it by 512 gives the largest block count whose byte total fits. `ckd_mul` allows that result and refuses one more block. A fixed-size plan still needs a separate decision for zero blocks.

## Connect to Umicom OS and Kernel

An image inspector can validate counts before reporting a byte requirement. Kernel code may need a freestanding arithmetic helper with the same input units and refusal behavior. A good count alone says nothing about the availability of memory or the identity of a drive.

## Trace the logic

~~~text
IF THE DESCRIPTOR REQUIRES AN ITEM AND count IS ZERO
    REFUSE THE REQUEST
MULTIPLY count BY bytes per block INTO temporary
IF THE RESULT FITS
    SAVE THE BYTE COUNT
~~~

~~~c
static bool block_bytes(size_t blocks, size_t *bytes)
{
    /* The toy descriptor requires a nonempty run of 512-byte blocks. */
    if (blocks == 0U) return false;
    size_t candidate;
    if (ckd_mul(&candidate, blocks, (size_t)512)) return false;
    *bytes = candidate;
    return true;
}
~~~

## Build and run one practice case

1. Open a PowerShell terminal with GCC, CMake and Ninja on the search path. To use Clang, select `clang` in the configure command and choose a separate build directory in all three commands. Check that the selected C compiler and its headers provide `<stdckdint.h>`. If that header is missing, the final lesson demonstrates `size_t` guards using only older headers.
2. Open `labs/native/checked-integers/multiply.c`. Read the successful case and at least one refusal case.
3. Run the commands one at a time. Stop on the first error so an earlier executable cannot be mistaken for the latest build.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/native/checked-integers -B build/checked-integers -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build/checked-integers --target checked-integers-multiply
ctest --test-dir build/checked-integers -R "^lesson[.]checked-integers[.]multiply$" -V --no-tests=error
~~~

Expect one passing test and this line of program output.

~~~text
Eight blocks need 4096 bytes. The oversized count was refused.
~~~

## Try a change

Use 4096 bytes per practice block everywhere in the example. Base the edge case on `SIZE_MAX / 4096`. Work out the expected byte count for eight blocks before rerunning.

## If a result differs

If both large counts pass, ensure the operands are passed to `ckd_mul` independently. Passing `count * width` would compute the result before it is checked.

## Read the C language reference

[WG14 N3220, section 7.20.1 on checked integer operations](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=326)

[Course contents](index.md) · [Previous: Separate subtraction from a debit rule](45-separate-subtraction-from-a-debit-rule.md) · [Next: Publish a complete record size](47-publish-a-complete-record-size.md)
