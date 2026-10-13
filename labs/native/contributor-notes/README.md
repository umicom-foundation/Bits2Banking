# First C23 contributor laboratory — Umicom Notes

This is a teaching implementation of a small in-memory Notes model, built as a real C23 static library and linked into a programme and independent tests. It does not duplicate Framework's production document management, save to disk, alter Git, execute PowerShell or connect to a database.

## Windows (PowerShell 7, GCC from MSYS2 UCRT64)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\contributor-notes" -B ".\output\learning-build\contributor-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\contributor-notes" --parallel 2
ctest --test-dir ".\output\learning-build\contributor-notes" --output-on-failure
& ".\output\learning-build\contributor-notes\btb-contributor-notes-demo.exe"
```

## Linux (installed GCC, Ninja, CMake)

```bash
cmake -S labs/native/contributor-notes -B output/learning-build/contributor-notes -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build output/learning-build/contributor-notes --parallel 2
ctest --test-dir output/learning-build/contributor-notes --output-on-failure
./output/learning-build/contributor-notes/btb-contributor-notes-demo
```

Expected independent CTest registrations: **8** (7 selected cases plus the demonstration). Unit tests include normal addition, updates, bounds, exhaustion, nonexistent records, invalid inputs and copied ownership. No tests use arbitrary delays or internet access. The demo clearly states that notes exist **only in memory** and will disappear when it exits.

## Optional existing Framework integration

If a *compatible installed Umicom Framework CMake SDK* is available, enable `-DBTB_ENABLE_FRAMEWORK_PLANNER_EXAMPLE=ON -DCMAKE_PREFIX_PATH="<actual installation prefix>"` during CMake configure. The extra executable calls `umi_build_automation_*` through `Umicom::build`. It is not compiled or tested in the standalone default build, and never modifies the Framework.

## Safe experiments

1. Run the demonstration as supplied and record its output.
2. Change the first note text in `main.c` **only in your review copy**, rebuild, rerun and compare outputs.
3. Read `notes.h` and explain who owns the Notes array and why `BtbNotesRead` copies its result.
4. Run `ctest -N` to list the tests, then run `ctest --output-on-failure`.
5. Discuss why this tiny teaching model is *not* sufficient for production bank records: there is no durable storage, authentication, audit trail, concurrency or transaction boundary.
