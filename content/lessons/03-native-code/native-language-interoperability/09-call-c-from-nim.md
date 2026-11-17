<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/09-call-c-from-nim.md

PURPOSE:
Teach generate c from nim while preserving the boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Generate C from Nim while preserving the boundary

[Course contents](index.md) · [Previous](08-call-c-from-odin.md) · [Next](10-forward-a-call-in-assembly.md)

## Two compilation stages
The Nim C backend produces C source and then uses a C compiler to create machine code. The resulting executable still needs correct types and ownership. Generated C is not automatically a promise that any C library can free Nim objects.

The declaration uses cint, importc with the exact C symbol, and cdecl for the C calling convention. It passes an integer value, not a Nim string, sequence or managed object. The counting function remains in the existing C archive.

## Build a small program
1. Check nim --version and gcc --version. Select the same target as the common archive.
2. Read main.nim. Indentation groups the statements inside the loop and if branch.
3. Keep checks enabled. The explicit mismatch branch calls quit with status 1.
4. From the repository root, run:

~~~powershell
$activityArchive = (Resolve-Path build/activity-adapters/libbtb-activity-adapters.a).Path
nim c --cc:gcc --mm:orc "--passL:$activityArchive" --nimcache:build/nim-cache --out:build/nim-activity.exe labs/languages/nim-activity/main.nim
& .\build\nim-activity.exe
~~~

The C backend may place generated files under build/nim-cache. Inspect them after a successful compile to see the external call, but make changes in the Nim source; generated files can be replaced on the next build.

## Interpret results and memory behaviour
Expect the same five checked lines as the Fortran example. ORC is a Nim memory-management mode; it does not change who owns an arbitrary C allocation. If a Framework API returns an owned object, use its documented destroy function. If it borrows a buffer only during a call, keep that buffer alive for the whole call.

## Exercise and answer
Why use cint instead of int? The C function declares int, while Nim's general integer follows its own platform rules. Does compiling through C remove Nim's runtime requirements? No. The generated program can still contain runtime support. This example avoids passing managed storage across the ABI rather than pretending that support does not exist.

[Nim's foreign-function manual](https://nim-lang.org/docs/manual.html#foreign-function-interface-importc-pragma) explains importc. Start Learning Nim for indentation, let and proc before this lesson.

## Read the complete source

[labs/languages/nim-activity/main.nim](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/nim-activity/main.nim)
