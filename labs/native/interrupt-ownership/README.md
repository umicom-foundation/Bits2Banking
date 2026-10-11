# Interrupt ownership in C23

A complete, hosted state-machine exercise. The source claims an interrupt-like resource, checks owner/generation identity and refuses release during an unfinished operation. It does not control CPU registers, real devices or interrupts.

Run from PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\interrupt-ownership" `
    -B ".\output\learning-build\interrupt-ownership" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\interrupt-ownership" --parallel 2
ctest --test-dir ".\output\learning-build\interrupt-ownership" --output-on-failure
```

Two tests should pass. See [Lesson 112](../../../content/lessons/05-engineering/112-interrupt-ownership-and-critical-sections.md) for the state diagram. This model is used as one linked dependency by the service-recovery exercise; it is not duplicated.
