<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/57-separate-source-spelling-from-wire-format.md

PURPOSE:
Separate source spelling from wire format

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate source spelling from wire format

## Before you begin
Read the bytecode lesson and the preceding numeric-token walkthrough. Open tests/test_integer_literals.c, src/bytecode.c and include/umicom_c/profile.h. The useful distinction is between what source accepts and what the runtime executes.

## One value, one existing operation
A constant emits UMC_PUSH with an int32 operand. Hexadecimal and binary do not need their own opcodes. The runtime does not need to know the original radix to execute addition, comparison or return.

The numeric wire test compiles three complete programs returning 42. They spell it as decimal, hexadecimal and binary. The literal starts at byte offset 22 in each program, and return starts at offset 15. That makes their entire serialized output identical, including source locations.

~~~text
Header: U M C B, version 1, reserved 0, count 2
Record 1: PUSH, value 42, source offset 22
Record 2: RETURN, reserved operand 0, source offset 15
~~~

Read the literal expected byte array. The operand and offsets are little-endian: their lowest byte appears first. This expected array is written independently of the encoder. A test that only encodes then decodes with the same implementation could miss a shared mistake in both directions.

## Source locations are still observable
Different spellings do not always produce identical artifact bytes. If a longer literal moves a later operator, that operator's source offset changes. The test deliberately uses a single constant so no later emitted operation moves. Do not remove location checks to force unrelated programs to have the same digest.

Run the focused wire check from your configured source directory:

~~~powershell
ctest --test-dir build -R "umicom.c.integer-literals.wire" --output-on-failure --no-tests=error
~~~

Then run the CLI comparison example. Equality still selects existing format 2 because it uses a comparison operation, not because the constants have prefixes.

~~~powershell
.\build\bin\umicom-c.exe compile examples\integer_literals.uc build\numeric-comparison.umcb
.\build\bin\umicom-c.exe exec build\numeric-comparison.umcb --max-steps 4
.\build\bin\umicom-c.exe trace-bytecode build\numeric-comparison.umcb
~~~

Choose an unused output path. Expect two pushes of 42, an equality result of 1, and return. A three-step budget must fail before publishing a completed result. The CLI regression checks that source and bytecode traces agree and that failed compilation does not leave an output artifact.

## Advertise the correct component
The compiler mask now includes hexadecimal and binary source bits, 32 and 64. Added to its earlier mask of 7, that is 103. The runtime still reports 27. An editor can query the compiler before offering a source form. A runtime-only consumer should query execution and wire capabilities instead.

~~~c
uint32_t grammar = umc_compiler_profile(UMC_PROFILE_FEATURES);
if ((grammar & UMC_FEATURE_HEXADECIMAL_LITERALS) != 0U) {
    /* Offer the documented bounded hexadecimal spelling. */
}
~~~

This declaration is not a signature or build receipt. Keep header, library, source and toolchain identity separately when qualifying a deployment.

## Recovery exercise
Imagine that source compilation succeeds but an older runtime rejects the artifact. Inspect the emitted operations and format version before assuming the radix is at fault. A comparison program needs comparison support; a single constant uses the earlier arithmetic format. Select a qualified matching runtime. Never relabel a format-2 artifact as format 1 to bypass admission checks.

[Course contents](index.md) · [Previous lesson](56-read-hexadecimal-and-binary-source.md) · [Next lesson](58-test-source-spans-without-a-terminator.md)
