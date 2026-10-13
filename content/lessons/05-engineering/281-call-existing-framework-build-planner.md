# Chapter 281 — Call the existing Framework build planner from C23

**Bits to Banking · Optional Advanced Unit · Native architecture**  
**Time:** 40–60 minutes · **Prerequisite:** working C23 toolchain and understanding of public interfaces.

## Framework capability first

Before adding application code, search Umicom Framework for a suitable public contract. For deciding which applications and tests may be affected by changed files, Framework already provides `UmiBuildAutomation` in `include/umicom/build/automation.h`. It understands scopes, changed paths, shared providers and consumers, and action categories including configure, build, test and documentation. Our educational repository must **reuse** this component rather than copy its implementation.

The optional `labs/native/contributor-notes/framework_planner_example.c` contains a real **consumer** of the public Framework API. It does not implement Git, a compiler parser or a competing planner.

## A controlled fictional example

Imagine a changed public Framework header. We register a Framework scope as a shared provider, and a Notes application scope as a consumer. We then provide a fictional changed path and ask Framework to produce its plan. The model should select the direct Framework scope and the inherited Notes consumer.

```c
UmiBuildAutomation *planner = NULL;
UmiBuildAutomationChange changedFile;

if (umi_build_automation_create(&planner) != UMI_STATUS_OK) {
    /* Report unavailable planning resources to the caller. */
}
/* Scope registration and cleanup are shown in framework_planner_example.c. */
umi_build_automation_change_init(&changedFile,
    "framework/include/umicom/build/automation.h", 0);
```

The complete source handles failures, registers scopes, evaluates the changes and destroys the Framework-owned coordinator. Read the actual file for the complete programme before compiling it. Its input paths are fictional training values, **not** an observed Git working tree. A selected test is a *plan*, not a passed test.

## Build it only with a compatible installed SDK

The standard beginner Notes build does **not** require Framework. To enable the optional example, you must have an installed Framework CMake package exporting `Umicom::build`. Replace the placeholder below with an installation prefix that actually exists on your computer:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\contributor-notes" `
    -B ".\output\learning-build\contributor-notes-framework" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON `
    -DBTB_ENABLE_FRAMEWORK_PLANNER_EXAMPLE=ON `
    -DCMAKE_PREFIX_PATH="C:\ACTUAL\FRAMEWORK\INSTALL\PREFIX"
```

**Do not run this with the placeholder unchanged.** The course package does not claim the SDK is installed or that the optional target was tested on your machine. When configuration succeeds, run `cmake --build` and `ctest --test-dir` against that separate build directory.

## Architectural discussion

Framework's public ABI is the boundary. The Notes application only prepares typed inputs and reads the returned plan; it does not access internal `src/build/automation.c` state. Studio, Trader, TMS and OS have separate verification obligations. If your install exports different targets or an incompatible API, record the mismatch and consult the matching Framework revision rather than copying its source into the learning lab.

**Review:** What is an API consumer? Why is a selected test not a passed test? Why does an optional installed SDK target protect the standalone beginner build?

**Next:** [List and select native tests with CTest](282-select-native-tests-and-record-results.md).
