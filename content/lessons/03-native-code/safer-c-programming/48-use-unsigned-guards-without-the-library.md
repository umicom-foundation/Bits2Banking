<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/48-use-unsigned-guards-without-the-library.md

PURPOSE:
Use unsigned guards without the library

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use unsigned guards without the library

A C compiler can recognize C23 syntax even when a freestanding target or older library lacks a particular header. A small C guard can express the same range decision for `size_t` using basic unsigned arithmetic.

## Check before computing

For addition, compare `left` with `SIZE_MAX - right`. For multiplication, once the width is nonzero, compare `count` with `SIZE_MAX / width`. The result when the width is zero is zero. These formulas presume both operands already represent the intended nonnegative quantities.

## Look at an x86-64 object

In the optional Assembly object, a 32-bit `addl` computes `0x7fffffff + 1`. It sets the signed overflow flag because the value crosses the signed 32-bit limit. It leaves carry clear because the sum fits the unsigned 32-bit width. `seto` and `setc` observe those flags. Some disassemblers display `setb` for the same carry instruction. The example produces an object for inspection and provides no callable interface.

## Connect to the checked Umicom C profiles

These source files use ordinary C headers and a hosted C toolchain. A checked source-interpreter exercise can test an individual arithmetic operation, while a C application can expose a richer function and explicit output storage. A freestanding Umicom subsystem can adapt the unsigned guard where platform headers are unavailable.

## Trace the logic

~~~text
IF width IS ZERO, SAVE ZERO
ELSE IF count EXCEEDS MAXIMUM DIVIDED BY width, REFUSE
ELSE SAVE count TIMES width
~~~

~~~c
static bool size_product(size_t count, size_t width, size_t *bytes)
{
    /* Check the largest safe count before multiplying; skip division by zero. */
    if (width != 0U && count > SIZE_MAX / width) return false;
    *bytes = count * width;
    return true;
}

static bool size_sum(size_t left, size_t right, size_t *total)
{
    /* Subtraction is safe because right already has the destination type. */
    if (left > SIZE_MAX - right) return false;
    *total = left + right;
    return true;
}
~~~

## Build and run one practice case

1. Open a PowerShell terminal with GCC, CMake and Ninja on the search path. To use Clang, select `clang` in the configure command and choose a separate build directory in all three commands. The selected target uses ordinary headers available before C23. The other targets additionally require `<stdckdint.h>`.
2. Open `labs/native/checked-integers/fallback.c`. Read the successful case and at least one refusal case.
3. Run the commands one at a time. Stop on the first error so an earlier executable cannot be mistaken for the latest build.

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking"
cmake -S labs/native/checked-integers -B build/checked-integers -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build build/checked-integers --target checked-integers-fallback
ctest --test-dir build/checked-integers -R "^lesson[.]checked-integers[.]fallback$" -V --no-tests=error
~~~

Expect one passing test and this line of program output.

~~~text
The manual guards accepted 192 and kept it after overflow.
~~~

To inspect the optional x86-64 GNU-syntax Assembly sample, first create the build directory with the commands above. Use an x86-64 GCC or Clang toolchain and LLVM's object reader.

~~~powershell
gcc -c labs/native/checked-integers/inspect_add_flags.S -o build/checked-integers/add-flags.o
llvm-objdump -d build/checked-integers/add-flags.o
~~~

Look for the addition and both flag instructions. The object is for inspection. Leave it unlinked.

## Try a change

Before assembling the optional object, predict the encoded `add` and two flag-observation instructions. Think through what would change in the flags if the input register held `0xffffffff` before adding one.

## If a result differs

If a guard itself causes division by zero, inspect the short-circuit `&&` condition. If the disassembler shows no such section, verify that it read the newly assembled x86-64 object.

## Read the C language reference

[WG14 N3220, section 7.20.1 on checked integer operations](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3220.pdf#page=326)

[Course contents](index.md) · [Previous: Publish a complete record size](47-publish-a-complete-record-size.md)
