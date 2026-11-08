<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/41-compare-signed-values-safely.md

PURPOSE:
Compare signed values without subtracting them

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare signed values without subtracting them

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

## Use the defined comparison operation

A tempting implementation compares left and right by subtracting them and checking the sign. That subtraction can overflow when one operand is the minimum signed value and the other is the maximum. The runtime instead uses the native signed comparison directly and stores 1 or 0. The widened arithmetic path remains for addition and multiplication, but comparison does not need an arithmetic difference.

## Trace the stack contract

Every binary comparison requires two values. The right operand is the last stack entry and the left operand is immediately below it. After comparing, the engine reduces the depth by one and writes the result into the surviving entry. Validation checks this shape before execution begins. Reserved instruction operands must still be zero; a comparison cannot use that field as a hidden literal.

## Use independent expected values

Read test_comparison_runtime.c. Its truth table includes negative values, equality and both orders of the signed extremes. Expected results are literal zeros and ones, not calls to a second copy of the runtime evaluator. Change the lesson expression to (-2147483647 - 1) < 2147483647. Expect 1. Reverse the values and expect 0; both executions should complete successfully.

## Keep result value and status separate

Zero is a valid comparison result, not an error code. The runtime return status states whether execution completed, while UmcResult.value carries the program answer. Framework adds its completed flag and phase for presentation. A UI that treats a zero answer as failure would reject every false comparison. Test the status and the value independently, including a successful false expression followed by a malformed request.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](40-layer-comparison-precedence.md) · [Next lesson](42-evaluate-comparison-operands.md)
