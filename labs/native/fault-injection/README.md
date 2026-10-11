# Make allocations fail on purpose

This exercise creates one Notes record, then simulates an allocator refusing the first or second requested allocation. When replacement fails, the original note remains unchanged. The test also counts outstanding allocations and requires zero after cleanup.

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\fault-injection" -B ".\output\learning-build\fault-injection" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\fault-injection" --parallel 2
ctest --test-dir ".\output\learning-build\fault-injection" --output-on-failure
& ".\output\learning-build\fault-injection\bits2banking-fault-injection.exe"
```

## Linux

```bash
cmake -S labs/native/fault-injection -B output/learning-build/fault-injection -G Ninja
cmake --build output/learning-build/fault-injection --parallel 2
ctest --test-dir output/learning-build/fault-injection --output-on-failure
./output/learning-build/fault-injection/bits2banking-fault-injection
```

You should see `1/1` passing test. The demonstration prints the stored title, body and revision. The implementation uses explicit byte lengths, so a failed operation never requires guessing how much memory an input occupies.

See [Lesson 64](../../../content/lessons/03-native-code/64-test-allocation-failures.md) and the [Umicom Framework allocator interface](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/base/memory.h). This is a standalone teaching model, not a second production document subsystem.
