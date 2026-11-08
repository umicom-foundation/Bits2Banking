<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/44-qualify-comparison-cli-workflows.md

PURPOSE:
Qualify comparison commands through the real CLI

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify comparison commands through the real CLI

## Prepare the exercise

Complete the earlier compiler inspection and trace exercises. Keep the Umicom C and Bits2Banking checkouts beside each other, and use comparison-capable Umicom C source. This exercise reuses the existing C23 compiler lab; it adds no second parser or interpreter.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/compiler-inspection -B build/compiler-inspection -G Ninja -DBUILD_TESTING=ON
cmake --build build/compiler-inspection --parallel 2
ctest --test-dir build/compiler-inspection --output-on-failure --no-tests=error
& ".\build\compiler-inspection\compiler-inspection.exe" --comparison --trace
```

Run each command separately and stop on errors. The comparison trace should contain eight rows and finish with Result: 1; inspection should report a peak of three values and eighty encoded bytes. These are expected observations to verify, not recorded passes.

## Cover the user-visible path

Unit calls cannot prove that command-line parsing, file ownership and printed output agree with the library. The CLI comparison check writes a source fixture, checks it, compiles a new artifact, inspects both forms, runs both forms and compares their traces. The fixture is the same eight-instruction expression used by this lesson, making the expected count and result easy to verify independently.

## Distinguish inspection counters

The expression has four PUSH operations, two arithmetic operations, one LESS and one RETURN. Its arithmetic counter remains two because that field retains its original meaning. Total instructions are eight and encoded size is eighty bytes. A comparison increases the instruction count but not the arithmetic counter. Stable field meaning matters to existing consumers more than making one counter include every new instruction kind.

## Preserve inputs and old outputs

Compilation creates a new output exclusively. The CLI check tries compiling to the same artifact again and expects refusal, then compares source and artifact hashes. Tracing and inspection must also leave their inputs unchanged. Use a fresh output name for your own exercise; do not delete a file merely because the compiler correctly refused to overwrite it.

## Record actual command evidence

Run the registered CLI group against the binary you just built and keep its complete exit and diagnostic output. A matching printed result alone is insufficient if the command exited unsuccessfully. Conversely, a failed budget command is expected only when its diagnostic states budget exhaustion and it publishes no result. Record the source revision, toolchain and executable path alongside the observation so an older binary is not mistaken for the current implementation.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](43-version-comparison-bytecode.md) · [Next lesson](45-reuse-comparisons-in-framework.md)
