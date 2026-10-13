# Chapter 249 — Connect Framework VCS and diagnostics to C23 evidence

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** ISO C23 · **Optional SDK target:** `btb-build-evidence-framework-demo`  
**Prerequisites:** Chapters 240, 242 and 245; installed compatible Framework C libraries.

## Why this matters

The standalone C23 lab is useful for verifying ownership and comparison logic, but it receives fictional records. A genuine integrated application should obtain working-tree facts through Umicom Framework's VCS service and parse compiler output through Umicom Framework's shared diagnostic service. This chapter introduces an **optional read-only adapter** that consumes those exact public types, rather than introducing another Git parser or another compiler grammar.

## Public dependencies, not private source

The integration file `framework_bridge.c` includes:

```c
#include "umicom/vcs/working_tree.h"
#include "umicom/build/diagnostic.h"
```

It accepts `UmiVcsWorkingTreeSummary` and `UmiBuildDiagnosticList`. The adapter copies the summary's complete commit ID into a `BtbEvidenceIdentity` and projects complete, bounded diagnostic fields into local teaching records. No parsing of `.git` files or raw `CMake Error` text takes place inside the adapter. A long source path or message is **refused**, not cropped.

Because Framework owns the actual Git command execution, the adapter does not create a PowerShell/Python helper or an alternative process runner. When an application needs richer status, it should use Framework's `UmiVcsWorkingTreeRead` and `UmiVcsWorkingTreeDescribe` directly.

## Build the optional imported-library target

The default C23 laboratory builds without Framework. For genuine SDK reuse, the CMake project provides `BTB_ENABLE_FRAMEWORK_SDK=ON`. It calls:

```cmake
find_package(UmicomFramework CONFIG REQUIRED)
target_link_libraries(btb-build-evidence-framework
    PUBLIC btb-build-evidence Umicom::vcs Umicom::build)
```

These are **existing Framework exported targets**. Do not copy the C files under `framework/src/vcs` or `framework/src/build` into Bits2Banking. The installed SDK must match the compiler ABI and library architecture being used. For example, an MSYS2 UCRT64 GCC build must not link to a foreign MSVC runtime build.

After you have installed Framework to an appropriate SDK prefix, configure the optional target from your Bits2Banking root:

```powershell
cmake -S ".\labs\native\build-evidence" `
  -B ".\output\learning-build\build-evidence-sdk" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" `
  -DBTB_ENABLE_FRAMEWORK_SDK=ON -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence-sdk" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence-sdk" --output-on-failure
```

`C:\umicom\installed\framework` is **an example installation prefix**, not a claim that this directory already exists. Use the path where your Framework CMake package was actually installed. The current delivery has not compiled the SDK-linked target against your Windows Framework installation; this is a separate acceptance gate.

## Verify the read-only Framework example

After a successful SDK build, the executable supports a self-contained default demonstration and an optional Git observation:

```powershell
& ".\output\learning-build\build-evidence-sdk\btb-build-evidence-framework-demo.exe"
& ".\output\learning-build\build-evidence-sdk\btb-build-evidence-framework-demo.exe" `
  --repo "C:\umicom\umicomOS\framework"
```

The second command asks the existing Framework service to read the specified working tree. It does not fetch, stage, commit, switch branches or push. A valid detached commit is usable as a **build input identity**, but the fact that a detached HEAD builds cleanly does not authorise pushing it directly to `main`.

## Understand the limit of this proof

The optional demo parses a deliberately fictional warning using the **real Framework compiler parser**, then projects that record into the evidence model. It does not run a full build or capture a production transcript. It demonstrates source compatibility and linking when the SDK target is actually compiled, not end-to-end production release readiness.

The adapter also accepts a maximum of 24 projected diagnostics while Framework can retain more. If the projection is too small, it returns `FULL` and preserves the prior snapshot. Users must inspect the Framework's retained list and raw log rather than claim that missing items were harmless.

## Assessment

**Why make SDK use optional?** Standalone beginner lessons must compile without building the entire Framework. **What constitutes genuine reuse?** Link imported Framework libraries and consume supported public C APIs. **Why is a read-only demo still valuable?** It establishes ownership and ABI boundaries while making it impossible for a teaching exercise to mutate a real Git repository by accident.

**Next:** Chapter 250 explains repeatable builds across toolchains and operating systems.
