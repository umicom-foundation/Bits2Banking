<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/programming-across-languages/08-pass-two-integers-through-the-c-abi.md

PURPOSE:
Pass two integers through the C ABI

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Pass two integers through the C ABI

A **calling convention** tells separately compiled functions where to find their inputs and where to leave a result. A compiler and an assembler can build different files into the same program when they agree on these rules. The larger set of rules is called an **application binary interface**, or ABI.

## Read one call from both sides

The C declaration describes a function that takes two signed 32-bit numbers and returns a signed 32-bit number. The function receives completed amounts in whole pennies.

~~~c
extern int32_t UmiLessonBalanceDelta(int32_t received, int32_t booked);
~~~

In the Windows x64 ABI, these first two integer values occupy the low parts of RCX and RDX. The result uses EAX, the low part of the return register. This leaf function makes no other call and leaves the stack pointer alone. [Microsoft x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention)

~~~asm
UmiLessonBalanceDelta:
    movl %ecx, %eax
    subl %edx, %eax
    ret
~~~

The assembler uses source-first notation. The move copies `received` to EAX. The subtraction removes `booked` from that value. The return hands the result back to the C caller.

~~~text
ACCEPT received and booked as two signed integers
IF their mathematical difference fits 32 bits
    RETURN received minus booked
OTHERWISE report refusal
~~~

The compiled lesson puts the range check in C. The assembly leaf runs after that check.

## Build the native example

1. Open both lab sources linked below. Save them together in a practice folder as `main.c` and `delta_win64.S`.
2. Use a Windows x64 terminal with a 64-bit MinGW GCC or Clang toolchain set up. Run this GCC command in the practice folder.

~~~powershell
gcc -std=c23 -Wall -Wextra -Wpedantic main.c delta_win64.S -o signed-delta.exe
.\signed-delta.exe
~~~

3. Expect `Verified 7 signed delta rows and an absent output.` The first rows cover a positive difference, a negative difference and zero.
4. If the compiler reports an undefined `UmiLessonBalanceDelta`, check that both source filenames appear on the command line and that the name is spelled exactly as shown.

The register handoff is useful when reading Kernel or Framework assembly with a C interface. Keep the prototype and its width beside the call site so a reader can check the inputs before working through the instructions.

[Course contents](index.md) · [Previous lesson · Plan a first Umicom change](07-plan-a-first-umicom-change.md) · [Next lesson · Keep a signed difference in range](09-keep-a-signed-difference-in-range.md) · [HTML edition](../../../courses/programming-across-languages/lessons/08-pass-two-integers-through-the-c-abi.html) · [Check a signed difference in C23](../../../labs/native/shared-signed-delta/main.c) · [Subtract two signed inputs in Windows x64 Assembly](../../../labs/native/shared-signed-delta/delta_win64.S)
