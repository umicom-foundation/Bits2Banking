# Chapter 250 — Cross-platform C23 build reproducibility and provenance

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Tools:** CMake, Ninja, GCC, Clang, sanitizers  
**Prerequisites:** Chapters 243–249.

## Why this matters

Passing an automated test on one Linux compiler is strong evidence about that particular build. It is not proof that a Windows UCRT64 executable links correctly, that a GTK4 application packages required DLLs, or that a specific RISC-V Kernel image boots under QEMU. Professional engineering reports must state **where each test ran**, which source it used, what it covered and which acceptance steps are still outstanding.

The source language is C23, but compilers and runtime libraries vary. Warning support may differ, especially around recently adopted standard features. AddressSanitizer and UndefinedBehaviorSanitizer can identify mistakes missed by ordinary execution, but a clean sanitizer run is not a formal correctness proof.

## Build the standalone laboratory on Windows

From the Bits2Banking repository root in PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
cmake -S ".\labs\native\build-evidence" `
  -B ".\output\learning-build\build-evidence" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence" --output-on-failure
```

No new `.ps1` file is created. These are direct interactive invocations of the native toolchain and CTest. A PowerShell execution environment is not a reason to write application logic in PowerShell.

## Build the same source on Linux

With GCC or Clang and Ninja installed:

```bash
cmake -S labs/native/build-evidence -B output/learning-build/build-evidence -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/build-evidence --parallel 2
ctest --test-dir output/learning-build/build-evidence --output-on-failure
```

The implementation does not depend on GTK4, sockets or a file-system path convention. The same fixed-capacity contract should therefore run under a conforming hosted C23 toolchain. Record the actual compiler version; do not assume your colleague's environment is identical.

## Sanitizer qualification

For a separate Clang build directory:

```bash
cmake -S labs/native/build-evidence -B output/learning-build/build-evidence-asan -G Ninja \
  -DCMAKE_C_COMPILER=clang -DBUILD_TESTING=ON \
  '-DCMAKE_C_FLAGS=-fsanitize=address,undefined -fno-omit-frame-pointer' \
  '-DCMAKE_EXE_LINKER_FLAGS=-fsanitize=address,undefined'
cmake --build output/learning-build/build-evidence-asan --parallel 2
ctest --test-dir output/learning-build/build-evidence-asan --output-on-failure
```

Keep GCC and Clang outputs in separate build directories. Mixing previously compiled object files or CMake caches from different compilers creates misleading results. A sanitizer toolchain may not be supported on every Windows configuration; report unsupported test environments as **not run**, not passed.

## Evidence required for an Umicom integration

A Framework change can affect Studio, Trader, Bank and Umicom OS. Test Framework first and record its SHA. Then rebuild each affected consumer against the intended Framework pin, record the consumer SHA and pin, and perform product-specific smoke tests. For Windows desktop software, include startup from an icon without a developer PATH. For a Kernel change, record actual QEMU boot evidence separately from hosted unit tests.

The `BtbEvidenceCompare` model requires matching profile and toolchain labels. This is a simplified protection against comparing incomparable environments. A production evidence system additionally records compiler binary hashes, CMake cache changes, environment-variable policy, operating-system version, SDK artefacts and dependency lock files.

## Assessment

**Can GCC tests replace Windows UCRT64 verification?** No. **Do sanitizer tests alone certify production?** No. **Why record a source SHA and toolchain?** To make results attributable and repeatable. **Why use separate build directories?** To isolate CMake configuration, compiler flags and generated objects.

**Next:** Chapter 251 brings the entire investigation into one reviewed Umicom change.
