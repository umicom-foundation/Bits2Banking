<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/39-recognise-comparison-tokens.md

PURPOSE:
Recognise comparison tokens without reading past the source

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Recognise comparison tokens without reading past the source

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

## Start with a bounded span

A lexer turns source bytes into tokens. Its input is a pointer plus a length, so it must not assume that a terminating zero byte exists beyond the span. The comparison extension reads the current punctuation, then checks that another byte is available before looking for an equals sign. This permits < and <= without crossing the boundary at the final character. Token offsets still identify the first byte of the operator.

## Choose the longest supported spelling

For <=, consume both characters and produce one LESS_EQUAL token. For < =, whitespace ends the first token; the later bare equals sign is invalid. Equality uses ==, while assignment with = remains outside this language. Similarly, != is supported but unary ! is not. Supporting one spelling does not authorise every related operator. Read the four punctuation branches in lexer.c and identify exactly when the source position advances a second time.

## Exercise a boundary deliberately

Make a temporary copy of the lab source and replace the expression with 2 <= 2. Rebuild and expect a successful value of 1. Then try 2 < = 2 and expect a syntax diagnostic rather than execution. Record the operator byte and the one-based displayed column separately. For a lower-level exercise, pass a borrowed source span ending immediately after < to umc_compile; the parser must report the missing right operand without reading outside the span.

## Keep token tests distinct from execution tests

The source comparison regression cases include a spaced operator, a missing right operand, bare assignment and unsupported logical conjunction. Their expected outcome is a compile refusal with a zero published instruction count. A lexer accepting <= does not establish the meaning of the comparison; the parser and runtime still need their own checks. Keep the old arithmetic tests because this new punctuation shares the same comment, number and whitespace scanner.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](38-record-layered-trace-evidence.md) · [Next lesson](40-layer-comparison-precedence.md)
