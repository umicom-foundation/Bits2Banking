# Native C23 fleet-readiness teaching laboratory — Update 46

**Umicom Foundation · Sammy Hegab · MIT · ISO C23**

## What the executable actually does

It combines fictional observations for two hosts called `notes-gateway` and `notes-storage`. It calls the **existing** `BtbOpsEvaluate` supplied by Update 45 for each host; it does not create a new security, scheduling, backup or service-health engine. Results are `PENDING`, `BLOCKED`, `REVIEWABLE` or `RESTORED_ONLY`. The last state is specifically **not** approval for a failed proposed release.

No file or network I/O, shell spawning, SSH, actual host discovery, credential handling, operating-system service control or deployment is performed. Tests use fixed training values. Real reusable capability belongs in Umicom Framework.

## Dependencies

Updates 39–45 must be merged in the same `labs/native` folder. This project uses `add_subdirectory` to compile each prior independent library and its own regression tests. It does not copy their implementations into this module and does not modify those files.

## Windows PowerShell 7 build and test

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\fleet-readiness" -B ".\output\learning-build\fleet-readiness" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\fleet-readiness" --parallel 2
ctest --test-dir ".\output\learning-build\fleet-readiness" --no-tests=error --output-on-failure
& ".\output\learning-build\fleet-readiness\btb-fleet-readiness-demo.exe"
```

## Linux build and test

```bash
cmake -S labs/native/fleet-readiness -B output/learning-build/fleet-readiness-linux -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build output/learning-build/fleet-readiness-linux --parallel 2
ctest --test-dir output/learning-build/fleet-readiness-linux --no-tests=error --output-on-failure
./output/learning-build/fleet-readiness-linux/btb-fleet-readiness-demo
```

Both builds are separate verification gates. CTest counts include the previously delivered tests because the current CMake file imports those source directories additively.

## Code and ownership map

- `fleet_readiness.h` — public classroom value types, ownership, limits and outcomes.
- `fleet_readiness.c` — checked one-shot registration and read-only multi-host evaluation.
- `fleet_fixture.c/h` — fictional host evidence using the existing Update 45 fixture.
- `test_fleet.c` — named positive, negative, failure-atomic and 30,000-iteration deterministic cases.
- `main.c` — deterministic CLI demonstration with four decisions.

All mutable records are caller-owned. Inputs are borrowed for the duration of a call, and successfully attached host records are copied. Outputs change only on success. The example does not claim thread safety and should never be used as an approval or security authority for live systems.
