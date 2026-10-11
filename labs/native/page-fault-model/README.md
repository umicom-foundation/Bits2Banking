# Page-fault model — C23 laboratory

A C23 model of virtual pages, rights and refusals. It performs no operating-system memory mapping.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\page-fault-model" -B ".\output\learning-build\page-fault-model" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\page-fault-model" --parallel 2
ctest --test-dir ".\output\learning-build\page-fault-model" --output-on-failure
& ".\output\learning-build\page-fault-model\btb-page-fault-demo.exe"
```

The test checks permitted access, a write to executable code, unmapped-page refusal, duplicate mappings, address alignment, Sv39 canonical addresses and the fixed table capacity.

## Learn by changing it

Change the mapping of virtual page `0x2000` from read/write to read-only. Explain which simulated operations will now fail, then run the tests again. Restore the mapping to return to the passing baseline.

The model is separate from the real allocator and trap path in [Umicom Kernel](https://github.com/umicom-foundation/umicom-kernel).
