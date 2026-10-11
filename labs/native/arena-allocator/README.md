# A bounded arena for temporary Notes reports

An **arena** is one caller-owned region of memory. The programme places several temporary objects into that region and releases them together by returning to a checkpoint. It avoids a separate heap allocation for every object, but it does not extend the region's lifetime.

The example builds a Notes review report containing a heading and a summary. It never saves that report to disk. The test checks alignment, invalid alignments, insufficient capacity, rollback after failure, and checkpoints.

## Windows (MSYS2 UCRT64 compiler)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\arena-allocator" -B ".\output\learning-build\arena-allocator" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\arena-allocator" --parallel 2
ctest --test-dir ".\output\learning-build\arena-allocator" --output-on-failure
```

## What to inspect

Open `arena.c` and find `available - padding`. Observe that the programme checks `padding <= available` before subtracting, preventing the subtraction from wrapping. Find the place where `*outMemory` is assigned. Every possible failure must happen before that assignment.

Change the workspace from 512 bytes to 16 bytes and build the demo again. It should report failure without writing beyond the end of the storage. Restore 512 bytes when finished.

**Ownership:** `workspace` belongs to `main`. The arena borrows it. The title and body pointers are also borrowed, and must not be used after `BtbArenaRewind` or after `workspace` leaves scope.

[Read Lesson 68](../../../content/lessons/03-native-code/68-arenas-and-checkpoints.md).
