<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/50-qualify-negation-through-the-cli.md

PURPOSE:
Qualify negation through source and bytecode commands

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Qualify negation through source and bytecode commands

## Before you begin
Build the current Umicom C checkout using its documented native preset. Open examples/logical_not.uc. Keep the binary and source from the same build, and choose a new artifact name when compiling bytecode.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe check examples/logical_not.uc
.\build\windows-ucrt64-debug\bin\umicom-c.exe run examples/logical_not.uc --max-steps 4
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace examples/logical_not.uc
~~~

Run each command separately. The example's intended result is 1 with four executed instructions. Its leading comment is source metadata; it is not executable code.

## Compare two execution paths
Compile to a new file, then run that artifact:

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe compile examples/logical_not.uc build/negation-practice.umcb
.\build\windows-ucrt64-debug\bin\umicom-c.exe exec build/negation-practice.umcb --max-steps 4
.\build\windows-ucrt64-debug\bin\umicom-c.exe trace-bytecode build/negation-practice.umcb
~~~

1. Compare the source and bytecode result.
2. Compare the trace operations and source offsets.
3. Repeat execution with a budget of three and expect a nonzero failure status.
4. Attempt compilation to the same existing artifact and verify that its bytes remain unchanged.

## Automated regression
The umicom.c.cli-logical-not CTest performs these checks through the real command, including the existing comparison-format header. The library tests exercise lower-level boundaries independently.

~~~powershell
ctest --test-dir build/windows-ucrt64-debug --output-on-failure -R "umicom[.]c[.](logical-not|cli-logical-not)"
~~~

## Recovery and interpretation
If compile refuses an existing destination, use another filename; do not delete the source to clear the error. If execution reports an unsupported bytecode profile, inspect the runtime version rather than rewriting the format marker.

A guest running the canonical runtime can consume supported operations, but this CLI test does not prove that a complete compiler or editor runs inside the Kernel. Keep hosted compiler evidence, freestanding linking and guest execution separate.


[Course contents](index.md) · [Previous lesson](49-observe-negation-failures-and-budgets.md) · [Next lesson](51-query-the-linked-compiler-and-runtime.md)
