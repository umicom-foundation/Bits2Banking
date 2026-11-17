<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/08-call-c-from-odin.md

PURPOSE:
Teach select an explicit c library from odin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select an explicit C library from Odin

[Course contents](index.md) · [Previous](07-call-c-from-d.md) · [Next](09-call-c-from-nim.md)

## Learn the source vocabulary
A package groups Odin source files. import loads Odin code such as core:fmt. foreign import names a compiled library instead. The activity collection is a build-time location supplied by the user, so the source does not embed a private drive path.

The foreign block declares BtbActivityNext using proc "c" and c.int. The trailing three hyphens mean that another object supplies the body. Odin's default int must not be assumed to be the same as C int on every target.

## Prepare and build
1. Build libbtb-activity-adapters.a with lesson 1's matching C toolchain.
2. Check odin version and install the compiler's required platform linker. Consult the official Odin setup instructions for your platform.
3. Read the source before building. It performs five calls and returns process status 1 on any unexpected value.
4. Run from the repository root:

~~~powershell
$activityLibrary = (Resolve-Path build/activity-adapters).Path
odin build labs/languages/odin-activity/main.odin -file "-collection:activity=$activityLibrary" -out:build/odin-activity.exe
& .\build\odin-activity.exe
~~~

On Linux, use an absolute archive directory for the same collection and an output name without .exe. The source intentionally names the GNU archive. A library produced by a different object format or architecture must be rebuilt for the selected target; renaming a library is not a conversion.

## What success means
Expected output is the five-line sequence described in the Fortran lesson. It establishes this small integer boundary only. It does not establish a full Framework binding, GUI backend or debugger integration for Odin. If the linker rejects the archive, keep the diagnostic and inspect target compatibility before changing source.

## Exercise and answer
Why supply a library collection? It keeps the source portable and makes the chosen dependency visible in the build command. Why use c.int? It records the C ABI width rather than guessing from Odin's convenient native integer type.

[Odin foreign-system documentation](https://odin-lang.org/docs/overview/#foreign-system) explains library collections and calling conventions. The introductory Odin course explains packages and procedures before this exercise.

## Read the complete source

[labs/languages/odin-activity/main.odin](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/odin-activity/main.odin)
