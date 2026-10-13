# Change-impact and verification-evidence laboratory (C23)

**Bits to Banking · Major Update 36 · Umicom Foundation · Sammy Hegab**

This is a **teaching model**: a bounded dependency graph maps a reviewed change to potentially affected components and required evidence categories. It does not parse Git status, run tests, read files, modify a repository or approve production publication. Live Git, compiler, build and test observation belong to **Umicom Framework**, whose stable C ABI remains authoritative.

## Ownership and scope

The real Framework already implements source-change classification and build planning in `umicom/build/automation.h` through `UmiBuildAutomation`. **Use that existing Framework service in real applications; do not transplant this classroom algorithm into Studio or OS.** The optional `framework_example.c` demonstrates the Framework planner itself. For learning its underlying graph reasoning, the caller supplies at most 12 named modules, explicit dependency edges, a full 40- or 64-character hexadecimal source revision, and the set of changed modules. The planner propagates impact **from a changed dependency to its dependants** and produces the union of the affected components' required verification gates. The evaluator compares that plan against copied evidence for the same revision. There is no heap allocation, concurrency, threading or persistence.

`impact.h` defines the public teaching contract; `impact.c` validates and implements it; `impact_demo.c` shows a **fictional** Framework-to-Studio-and-OS example; `test_impact.c` contains named tests. Input/output storage is caller-owned. The graph takes copies of module names; no caller-provided string pointer is retained. Malformed input, capacity errors, duplicated edges and dependency cycles cannot partially modify the output object.

The fixed capacities are teaching limits, not assumptions about a production application's modules or tests. Tests verify bounds, invalid revisions, graph cycles, transitive impact, divergent gate states, dropped diagnostics, stale evidence, incomplete logs and output preservation.

## Windows UCRT64: configure, compile, test and inspect

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact" --parallel 2
ctest --test-dir ".\output\learning-build\change-impact" --output-on-failure
& ".\output\learning-build\change-impact\btb-change-impact-demo.exe"
```

Expected: **43 named tests**, including the executable demonstration. The demonstration intentionally reports `BTB_REASON_NOT_RUN_GATE` when the fictional OS boot evidence is absent. Running the CTest suite does **not** prove an actual Umicom OS image boots.

## Linux / GCC / Clang

```sh
cmake -S labs/native/change-impact -B output/learning-build/change-impact -G Ninja -DCMAKE_C_COMPILER=gcc -DBUILD_TESTING=ON
cmake --build output/learning-build/change-impact --parallel 2
ctest --test-dir output/learning-build/change-impact --output-on-failure
```

For a Clang sanitizer configuration, use a separate build directory and `-DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS='-fsanitize=address,undefined -fno-omit-frame-pointer -g' -DCMAKE_EXE_LINKER_FLAGS='-fsanitize=address,undefined'`.

## Optional real Framework SDK consumer

An **installed, compatible** Umicom Framework SDK is required for this optional consumer. It links to actual `Umicom::vcs` and `Umicom::build` CMake targets, uses `UmiVcsWorkingTreeRead`/`UmiVcsWorkingTreeDescribe` for a **read-only** repository snapshot, `umi_build_parse_diagnostic_line` for a sample compiler message, and the real `umi_build_automation_*` scope/change/plan API to demonstrate source-impact selection. It does not contain another Git or compiler parser.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact-framework" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" `
    -DBTB_WITH_UMICOM_FRAMEWORK=ON -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact-framework" --parallel 2
& ".\output\learning-build\change-impact-framework\btb-framework-readonly-example.exe" "C:\umicom\Umicom-Applications"
```

The prefix path is an **example**, not a claim that an SDK is installed there. If CMake cannot find a compatible SDK, report this optional gate as **not run**. Do not compile internal Framework `.c` files into this lab to bypass dependency discovery. The SDK consumer is intentionally a separate binary and does not declare that module-level impact can be inferred automatically from filenames.

## Important verification boundaries

- `BtbImpactAssess` returning zero reasons means **suitable for further human review**, never permission to push, deploy, trade, make payments or publish a release.
- A successful C23 unit test is not evidence of a Windows UCRT64 build, a GTK4 application start, a CTest integration run, QEMU boot, packaged installer, or an authentic Framework SDK build.
- The `sourceRevision` matches a supplied full commit identifier. The lab does **not** verify its existence, the binary's source provenance or the trustworthiness of incoming evidence. Real evidence must be acquired by approved Framework services and a reproducible build.
- Git source-preservation rules apply: do not use `reset --hard`, `clean -fd`, forced pushes or automatic overwrites. Review conflicts manually.
