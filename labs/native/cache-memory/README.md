# Cache and memory access laboratory

This complete C23 program reads the same 1,048,576 values in two different orders. Both methods must produce the same total. The elapsed time can differ because reading nearby addresses often makes better use of CPU caches, though processor design, compiler optimisations and other activity also affect timings.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\cache-memory" -B ".\output\learning-build\cache-memory" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cache-memory" --parallel 2
ctest --test-dir ".\output\learning-build\cache-memory" --output-on-failure
& ".\output\learning-build\cache-memory\umicom-cache-memory.exe"
```

## Build on Linux

```bash
cmake -S labs/native/cache-memory -B output/learning-build/cache-memory -G Ninja -DCMAKE_C_COMPILER=gcc
cmake --build output/learning-build/cache-memory
ctest --test-dir output/learning-build/cache-memory --output-on-failure
./output/learning-build/cache-memory/umicom-cache-memory
```

Experiment by changing the dimensions while keeping the total array size manageable. Compare Debug and Release builds, and do not assume one timing measurement proves the presence or exact size of a processor cache.
