# Owned Notes — a C23 memory-management laboratory

This application holds a small journal of Umicom development tasks in memory. Each note owns its title and body, so changing or releasing the caller's input strings does not change the saved note.

The laboratory is intentionally independent of the production Umicom Framework document services. It teaches the ownership decisions that those services must make. Applications built on Umicom Framework should consume Framework-owned document APIs instead of copying this teaching implementation.

## Build on Windows with PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\owned-notes" -B ".\output\learning-build\owned-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\owned-notes" --parallel 2
ctest --test-dir ".\output\learning-build\owned-notes" --output-on-failure
& ".\output\learning-build\owned-notes\bits2banking-owned-notes.exe"
```

## Build on Linux

```bash
cmake -S labs/native/owned-notes -B output/learning-build/owned-notes -G Ninja
cmake --build output/learning-build/owned-notes --parallel 2
ctest --test-dir output/learning-build/owned-notes --output-on-failure
./output/learning-build/owned-notes/bits2banking-owned-notes
```

## Observe what is owned

Open `notes.c`. `BtbOwnedPair` allocates copies before `BtbNoteStoreReplace` releases the old contents. `BtbReserve` uses a temporary pointer for `realloc`; if allocation fails, it leaves the earlier array intact. `BtbNoteStoreDestroy` releases all owned memory.

The test copies an input title, changes the original caller buffer and verifies that the saved title did not change. It also verifies refusal of a too-small read buffer and of a replacement with an excessively large body.

## Change one thing

Extend `main.c` to add a second task. Print both task IDs. Observe that removing a note does not renumber the remaining note. After that, add one new regression assertion to `test_notes.c`.

The complete lesson is [Memory ownership in C23](../../../content/lessons/03-native-code/58-memory-ownership-in-c23.md).
