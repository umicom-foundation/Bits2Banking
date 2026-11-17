<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/07-call-c-from-d.md

PURPOSE:
Teach call the c bridge with d betterc.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Call the C bridge with D BetterC

[Course contents](index.md) · [Previous](06-call-c-from-fortran.md) · [Next](08-call-c-from-odin.md)

## Distinguish D from BetterC
D is a native language with a larger runtime and standard library. BetterC selects a restricted mode useful for embedding in C programs. It does not make arbitrary D code valid without a runtime. This example uses fixed arrays, C linkage and C printf; it does not use classes, garbage collection or exceptions.

## Read the example
1. Find extern(C) on BtbActivityNext. This preserves the name and calling convention expected by the C archive.
2. Find extern(C) int main. This program uses a C entry point.
3. Read nothrow and @nogc. They constrain this D code; they cannot inspect the internals of an external C function automatically. Our known C model does not allocate or throw.
4. Follow the fixed input and expected arrays. A mismatched result returns 1 even when assertions are disabled.

## Compile with LDC
Check ldc2 --version, then use an LDC target and linker compatible with the archive from lesson 1. On a native Linux host, from the repository root:

~~~bash
ldc2 -betterC labs/languages/d-activity/main.d build/activity-adapters/libbtb-activity-adapters.a -of=build/d-activity
./build/d-activity
~~~

On Windows, use the same source and archive with a compatible LDC Windows target, and use -of=build/d-activity.exe. Run it with & .\build\d-activity.exe in PowerShell. Linker and C runtime configuration must match the installed toolchain; a Linux command copied into Windows does not establish compatibility.

Expect the same five lines as the Fortran client, including rejection of -1 and 1000. If LDC is not installed, record that result explicitly. Do not describe a source inspection as an executed BetterC test.

## Exercise and answer
Can you replace printf with an arbitrary managed-library function because the source is D? No. BetterC deliberately removes runtime facilities. Read the function's requirements before using it. Continue the existing Learning D course for modules, slices and contracts, then compare the two runtime modes.

[D BetterC documentation](https://dlang.org/spec/betterc.html) lists supported and unavailable facilities.

## Read the complete source

[labs/languages/d-activity/main.d](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/d-activity/main.d)
