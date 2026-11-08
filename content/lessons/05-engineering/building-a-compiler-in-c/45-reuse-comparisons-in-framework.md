<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/45-reuse-comparisons-in-framework.md

PURPOSE:
Reuse comparisons through Framework preview state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reuse comparisons through Framework preview state

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

## Keep one language engine

Framework provides request lifecycle and result presentation around Umicom C. It does not lex comparison symbols or evaluate them independently. The optional adapter links an installed Umicom C SDK, while this learning lab links its source target. Those are separate integration routes and need separate qualification. Reusing the engine prevents the CLI and future editor consumers from drifting in precedence, fuel accounting or failure behaviour.

## Invalidate a previous answer

Once caller storage is accepted, the adapter clears completed, the numeric result, instruction count and trace count before compiling a new request. A syntax error remains in the compiling phase. An operand arithmetic error remains in the executing phase and can retain attempted trace rows. Only an OK status with completed true permits a final-answer display. A false comparison with value zero satisfies that success contract.

## Detect stale dependency selection

The comparison consumer test requires headers declaring UMC_COMPARISON_PROFILE. If the header is missing, inspect CMAKE_PREFIX_PATH and the installation you selected. Matching headers do not prove that the linked library is current; execute the comparison cases after rebuilding the SDK and adapter. Do not duplicate the comparison implementation in Framework to work around an old installed dependency.

## Keep UI claims narrow

The optional preview executable demonstrates the service in a native process. It is not evidence that Studio Run is wired to this API or that a debugger can stop at comparison instructions. Record the adapter and process results separately from an editor interaction. The existing Studio audit and approved mockups define additional workflow checks; a library feature alone does not satisfy them.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](44-qualify-comparison-cli-workflows.md) · [Next lesson](46-qualify-comparisons-in-a-kernel-guest.md)
