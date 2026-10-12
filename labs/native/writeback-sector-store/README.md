# Write-back sector store — C23 laboratory

A four-sector, full-sector-write storage simulation. The student can stage a Notes document, observe the difference between staged and stable reads, flush successfully or partially, and simulate a crash. The export/import functions demonstrate complete bounded host-file images; they do not establish actual power-failure persistence.

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\writeback-sector-store" -B ".\output\learning-build\writeback-sector-store" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\writeback-sector-store" --parallel 2
ctest --test-dir ".\output\learning-build\writeback-sector-store" --output-on-failure
& ".\output\learning-build\writeback-sector-store\btb-sector-store-demo.exe"
```

## Linux terminal

```bash
cmake -S labs/native/writeback-sector-store -B output/learning-build/writeback-sector-store -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/writeback-sector-store --parallel 2
ctest --test-dir output/learning-build/writeback-sector-store --output-on-failure
./output/learning-build/writeback-sector-store/btb-sector-store-demo
```

## Source guide

- `block_store.h` declares the storage contract and its output statuses.
- `block_store.c` implements staged/stable sectors, bounded partial flush and failure-atomic import.
- `main.c` runs a Notes save scenario.
- `test_block_store.c` covers invalid input, partial flush, crash and exact file-image round trips.

Read [Lesson 133](../../../content/lessons/05-engineering/133-build-a-writeback-sector-store.md) before changing the tests. This is an in-memory pedagogical model: a real device may reorder writes or tear a sector, and `fflush()` is not a portable hardware persistence barrier.
