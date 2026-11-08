<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/43-version-comparison-bytecode.md

PURPOSE:
Version comparison bytecode without changing old artifacts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Version comparison bytecode without changing old artifacts

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

## Separate layout from capability

The wire layout remains an eight-byte header followed by nine-byte instruction records. Format 1 admits the existing arithmetic opcodes. Format 2 identifies programs that contain one or more comparison opcodes. The encoder selects the minimum required profile automatically. An old arithmetic program therefore retains exactly the same bytes, while an older runtime can reject comparison artifacts before interpreting their instructions.

## Keep opcode identity stable

PUSH through RETURN retain values 1 through 7. LESS, LESS_EQUAL, GREATER, GREATER_EQUAL, EQUAL and NOT_EQUAL append values 8 through 13. Never insert a new opcode in the middle of a published numbering scheme: existing files would acquire a different meaning. Source offsets and zero reserved flags retain their earlier rules. The version byte describes the program capability, not the host structure layout.

## Reject an inconsistent header

After decoding and validating the complete instruction sequence, the decoder checks that the header matches its required profile. A comparison labelled format 1 fails. An arithmetic-only program labelled format 2 also fails because the encoding is noncanonical. Changing one byte by hand is not a supported conversion. On failure, the published count is zero even if partial output slots were written; do not execute them.

## Inspect independent fixtures

The wire regression source contains literal byte arrays for a constant-return program and a four-instruction comparison. These expectations do not call the encoder to generate their own input. Follow the header bytes, opcode bytes and little-endian operands by hand. Then compare encode and decode results against those fixtures. Test truncation, trailing bytes and a mismatched version separately so a failure for the wrong reason cannot look like compatibility coverage.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](42-evaluate-comparison-operands.md) · [Next lesson](44-qualify-comparison-cli-workflows.md)
