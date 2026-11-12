<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/46-qualify-comparisons-in-a-kernel-guest.md

PURPOSE:
Qualify comparison execution in a Kernel guest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify comparison execution in a Kernel guest

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

## Reuse the allocation-free runtime

The Kernel diagnostic links the canonical Umicom C runtime into a native user program. The bytecode itself has no system calls or Kernel pointers. Its native envelope checks a calculation and exits through the established user-program contract. New selectors 9 through 12 cover true and false signed comparisons, a deliberately mislabelled wire version and fuel exhaustion before LESS. Earlier selectors retain their identities.

## Avoid hidden hosted dependencies

An automatic array initialised from many constants can cause a compiler to emit a memory-copy helper, especially without optimisation. The new guest helper uses immutable static instruction fixtures and writes result fields explicitly. This reduces reliance on optimiser choices, but only the freestanding O0 and O2 links can establish the actual emitted dependencies. Never infer that a source file is freestanding solely because it includes no hosted header.

## Separate host and guest evidence

The host envelope project compiles the actual guest entry function with the shared runtime and checks fifteen selector outcomes. It does not load ELF files or switch privilege levels. The guest validator separately runs selectors 0 through 12 under both optimisation levels, checks user-mode exit details, refuses terminal reentry and verifies frame restoration after destruction. Keep these reports separate rather than combining their counts into one claim of isolation.

## Preserve source identity across the run

The existing receipt records runtime sources, headers, recipes and generated images. Rebuild when any of them changes. A final ready marker is meaningful only with the expected case markers and matching identities. If a receipt refuses stale source, repair the build sequence rather than editing the receipt. Hardware execution remains another qualification environment beyond hosted checks and the emulated guest.

## Review and recover

If comparison syntax is rejected, inspect the selected Umicom C path and rebuild that dependency. Keep the full diagnostic and source identity. Preserve earlier artifacts and choose a new output name for compilation. Host, installed-SDK and guest checks are separate evidence layers.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/compiler-inspection/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-c/blob/main/docs/language.md)

[Course contents](index.md) · [Previous lesson](45-reuse-comparisons-in-framework.md)

[Next lesson](47-recognise-prefix-negation.md)
