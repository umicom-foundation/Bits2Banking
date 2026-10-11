# Call a native Assembly function from C

In this exercise, the same `AddTwoAssembly` function is implemented for the Windows x64, System V x86-64 and RISC-V64 calling conventions. The C23 test checks 100 pairs, including unsigned wraparound. It does not modify a real bank account or place a trade.

## Windows PowerShell — MSYS2 UCRT64

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\assembly-functions" -B ".\output\learning-build\assembly-functions" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\assembly-functions" --parallel 2
ctest --test-dir ".\output\learning-build\assembly-functions" --output-on-failure
& ".\output\learning-build\assembly-functions\bits2banking-assembly-functions.exe"
```

## Linux x86-64

```bash
cmake -S labs/native/assembly-functions -B /tmp/bits2banking-assembly-functions -G Ninja
cmake --build /tmp/bits2banking-assembly-functions
ctest --test-dir /tmp/bits2banking-assembly-functions --output-on-failure
/tmp/bits2banking-assembly-functions/bits2banking-assembly-functions
```

The expected test result is `1/1 passed`. The executable prints `C and Assembly agree on 100 value pairs.`

On RISC-V64, configure with a real RV64 cross-toolchain and run through the appropriate target environment. CMake does **not** claim that a host x86-64 test validates RISC-V instructions.

Explore the real equivalents in [Umicom Framework's Assembly learning examples](https://github.com/umicom-foundation/umicom-framework/tree/main/examples/learning/assembly). Then read [the Umicom Kernel first-boot guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/FIRST_BOOT.md) for the difference between an ordinary function and freestanding kernel entry code.
