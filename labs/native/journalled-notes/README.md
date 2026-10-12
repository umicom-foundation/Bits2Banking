# Journalled Notes — C23 laboratory

A single-record Notes application with an explicit write-ahead journal and simulated crash recovery. The laboratory consumes the `block_store.c` implementation from `../writeback-sector-store` as a shared CMake library; it does not reimplement the storage layer.

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\journalled-notes" -B ".\output\learning-build\journalled-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\journalled-notes" --parallel 2
ctest --test-dir ".\output\learning-build\journalled-notes" --output-on-failure
& ".\output\learning-build\journalled-notes\btb-journalled-notes-demo.exe"
```

## Linux terminal

```bash
cmake -S labs/native/journalled-notes -B output/learning-build/journalled-notes -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/journalled-notes --parallel 2
ctest --test-dir output/learning-build/journalled-notes --output-on-failure
./output/learning-build/journalled-notes/btb-journalled-notes-demo
```

## Files

- `journal.h` documents status values, the bounded Note record and deliberate interruption points.
- `journal.c` performs bytewise record encoding, CRC validation, write-ahead ordering and replay.
- `main.c` demonstrates a successful recovery after the stable journal was written.
- `test_journal.c` validates stale-revision refusal, replay, three interruption points and checksum corruption.

## Record format

Journal sector 0 and snapshot sector 1 each hold a 512-byte record. Byte offsets 0–3 hold the record type (`BTBJ` or `BTBS`); offset 4 is version 1; offset 5 is text length; offsets 6–13 hold a little-endian revision; offsets 14–17 hold the CRC32 of bytes 0–13 and the text; offsets 18 onward hold up to 80 text bytes. Unused bytes must be zero. A corrupt nonempty record is rejected rather than interpreted as absent.

## Limits

All simulated durability depends on complete 512-byte sector writes to the model's stable array. There is no live disk, filesystem, power-loss testing, parallel transaction service or guaranteed physical atomic sector write. CRC32 detects accidental corruption; it is not authentication. Read [Lesson 134](../../../content/lessons/05-engineering/134-write-ahead-journalling-and-recovery.md) for the explanation and exercises.
