<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/06-call-c-from-fortran.md

PURPOSE:
Teach pass a c integer correctly from fortran.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Pass a C integer correctly from Fortran

[Course contents](index.md) · [Previous](05-call-c-from-zig.md) · [Next](07-call-c-from-d.md)

## Understand the three essential declarations
Fortran is often used for scientific and numerical programs. A .f90 file uses free-form source: statements are not tied to the old fixed-form columns. The sample's iso_c_binding module supplies c_int, the kind of integer corresponding to C int.

BIND(C, name="BtbActivityNext") selects C interoperability and the exact external name. VALUE on current passes the integer itself. Without VALUE, a scalar argument is normally passed using reference-like behaviour; C would interpret an address as the integer input. A matching name alone cannot repair that error.

## Build and run
1. Finish the common archive in lesson 1.
2. Install or select a GNU Fortran compiler for the same target and runtime as the C compiler. Check gfortran --version; do not confuse an MSYS tool with a UCRT64 tool.
3. Read the full main.f90 source linked below. The interface block describes the C function; it does not implement the counting rule.
4. From the repository root, run:

~~~powershell
gfortran -Wall -Wextra -Werror -fcheck=all labs/languages/fortran-activity/main.f90 build/activity-adapters/libbtb-activity-adapters.a -o build/fortran-activity.exe
& .\build\fortran-activity.exe
~~~

Expected lines are -1 -> -1, 0 -> 1, 41 -> 42, 999 -> 1000 and 1000 -> -1. The program checks each value and ends with a nonzero status if a result differs. The loop index starts at 1 because these Fortran arrays use their default lower bound.

## Diagnose before changing the model
An unknown symbol points to the external name or archive. Nonsensical values point to ABI declarations, architecture or the wrong linked implementation. Do not remove VALUE to quiet an unrelated warning. An absent gfortran command is an unexecuted lab, not a language failure.

## Exercise and answer
Which three details must agree with int BtbActivityNext(int)? Answer: C linkage and external name, c_int for input and result, and VALUE for the input. Ordinary Fortran character strings are not C strings; a later text example needs a separate encoding and termination contract.

[GNU Fortran C interoperability](https://gcc.gnu.org/onlinedocs/gfortran/Interoperable-Subroutines-and-Functions.html) documents these declarations. Start Learning Fortran if program, implicit none and array indexing are unfamiliar.

## Read the complete source

[labs/languages/fortran-activity/main.f90](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/fortran-activity/main.f90)
