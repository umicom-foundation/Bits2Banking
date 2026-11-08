<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/40-layer-comparison-precedence.md

PURPOSE:
Layer arithmetic, relational and equality precedence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Layer arithmetic, relational and equality precedence

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

## Read a grammar as a call graph

The parser gives each precedence level a function. expression calls relational, relational calls additive, additive calls product, and product calls unary. A lower call completes the tighter operation before its caller emits the looser one. The earlier arithmetic expression body remains the active additive implementation, while its historical entry function is retained for review. This keeps multiplication-before-addition behaviour while allowing comparisons around complete arithmetic values.

## Predict the eight instructions

For 2 + 3 < 2 * 3, write PUSH 2, PUSH 3, ADD, PUSH 2, PUSH 3, MULTIPLY, LESS and RETURN. The two sides become 5 and 6 before LESS executes. The expected answer is 1. The peak stack is three values because the completed left side remains on the stack while the right-side multiplication reads its second operand. Compare your handwritten order with the lab trace, rather than deriving the expectation from the same parser.

## Separate grouping from mathematical notation

Operators at each binary level are left associative. Therefore 1 < 2 < 1 means (1 < 2) < 1: the first result is 1 and the final result is 0. It is not an interval test. Equality binds more loosely than relational operators, so 2 == 3 < 4 means 2 == (3 < 4) and also produces 0. Add parentheses when your intended grouping differs.

## Keep recursive depth bounded

Long sequences at one precedence level use a loop, not one recursive call per operator. Parentheses and unary signs still recurse through the existing depth limit. Adding a precedence level must not accidentally reset that depth. Exercise nested parentheses and a repeated comparison chain separately: they stress different parser resources, even when both produce short integer results.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](39-recognise-comparison-tokens.md) · [Next lesson](41-compare-signed-values-safely.md)
