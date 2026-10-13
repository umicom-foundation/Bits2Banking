# Episode 93 — Build your first native Umicom Notes programme in C23

**Bits to Banking · Umicom Foundation · Beginner video series**  
**Companion lessons:** Chapters 276–279 · **Suggested duration:** 14–18 minutes.

## Opening — A programme is more than a text file (0:00–3:00)

**On screen:** Show `c23-first-build-path-update37.svg`, then open the lab directory. Explain that `notes.h` defines the public contract, `notes.c` implements it, `main.c` uses it, `test_notes.c` checks it, and CMake prepares the build graph.

**Narration:** “We are building a small real Notes component. It is useful for learning but deliberately does not save files. Production data ownership, security and persistence belong to reviewed Framework services.”

## Check the toolchain (3:00–6:00)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
```

Explain what each tool does and how to read a missing-command error. If MSYS2 UCRT64 is not installed, demonstrate the documented setup first rather than pasting an arbitrary PATH.

## Configure, compile and test (6:00–12:00)

```powershell
cmake -S ".\labs\native\contributor-notes" -B ".\output\learning-build\contributor-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\contributor-notes" --parallel 2
ctest --test-dir ".\output\learning-build\contributor-notes" --output-on-failure
```

Read the generated build output. Confirm 8/8 only if eight tests actually executed and passed. Show `ctest -N` separately to demonstrate that listing tests is not running them.

## Run and inspect (12:00–15:00)

```powershell
& ".\output\learning-build\contributor-notes\btb-contributor-notes-demo.exe"
```

Open `notes.c` to explain bounded copying and preserved state on invalid input. Highlight a test that changes the caller's input buffer after addition and then verifies the stored note is unaffected.

## Class reflection (15:00–18:00)

Ask learners to state which results prove compilation, which prove the Notes tests, and which additional controls would be necessary before building a bank-grade Notes service. Do not claim that a passing standalone lab qualifies the whole Framework or OS.
