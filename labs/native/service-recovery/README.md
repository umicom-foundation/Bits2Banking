# Checked service recovery in C23

A fictional Notes service uses the established interrupt-ownership library, a checked in-memory revision counter and explicit failure/retry transitions. Accepted work is never silently replaced by unfinished work.

Run from PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\service-recovery" `
    -B ".\output\learning-build\service-recovery" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\service-recovery" --parallel 2
ctest --test-dir ".\output\learning-build\service-recovery" --output-on-failure
```

Two tests should pass. Read [Lesson 114](../../../content/lessons/05-engineering/114-restore-a-service-after-failure.md) to follow the accepted revision and interrupted revision.

This is not a durable transaction log: all state is held in process memory. It is not safe to use as a real filesystem, banking or kernel recovery mechanism.
