<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/42-evaluate-comparison-operands.md

PURPOSE:
Observe operand failures before a comparison

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Observe operand failures before a comparison

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

## Comparisons do not short-circuit

The current language evaluates both operands before the comparison instruction. It has no logical conjunction, logical disjunction or conditional branches. In 0 == (1 / 0), the left zero is pushed, then the right division is attempted. Division fails before EQUAL can run. A comparison result cannot excuse invalid arithmetic needed to compute an operand.

## Read a failed trace precisely

A failed trace includes the attempted instruction and its intact input stack. For the example above, expect three successful pushes followed by a rejected DIVIDE. There should be no EQUAL or RETURN row and no completed result. The low-level runtime leaves the caller result unchanged on failure. Framework clears its presentation result at request admission, so its failure view contains no stale successful answer. These are different ownership contracts serving different callers.

## Budget the comparison and the return

The basic 1 < 2 program has four instructions. Fuel of two stops before LESS with two operands still on the stack. Fuel of three permits LESS but stops before RETURN. The computed top value may already be 1, yet the program has not completed. A trace is evidence about attempted execution; only a successful final return publishes the result.

## Design a recovery exercise

Run the valid comparison, then submit the operand-fault expression and inspect the failure. Finally submit a one-constant program. Its shorter trace should expose only the new published count, even if old entries remain in the caller-owned buffer. Record status, phase, trace count and result validity for all three requests. Do not erase the failing observation when the later request succeeds.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](41-compare-signed-values-safely.md) · [Next lesson](43-version-comparison-bytecode.md)
