# Chapter 261 — Use the real Framework VCS and build SDK from C23

**Bits to Banking · Engineering track · Umicom Foundation**  
**Required for optional exercise:** a *compatible installed* Umicom Framework SDK.

## Why composition is the correct design

The previous educational batches taught queue ownership, build evidence and Git review. We now cross-check those abstractions against actual Framework capabilities before introducing production functionality. Umicom Framework already defines `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe`, `UmiVcsWorkingTreeDestroy` and `umi_build_parse_diagnostic_line`. Critically, it **also already implements production change-impact planning**: `UmiBuildAutomation` through `include/umicom/build/automation.h`, with `umi_build_automation_register_scope`, `umi_build_automation_add_change`, `umi_build_automation_evaluate`, `umi_build_automation_snapshot` and `umi_build_automation_item_at`. A new application should call these public APIs rather than copy a Framework `.c` file or implement another Git porcelain parser.

The optional `framework_example.c` is a **thin consumer**. It observes a selected working tree through Framework VCS, prints a bounded summary, parses one fictional compiler diagnostic through the real Framework build API, **then creates actual Framework build-automation scopes and evaluates a fictional changed public header**. The source uses genuine `umi_build_automation_*` entry points; it does not include a second production dependency selector. It does not run `git add`, `git commit`, `git push`, CMake, Ninja or CTest. The C23 change-impact planner remains a separate illustrative policy model and does not claim to convert arbitrary file changes into production module ownership automatically.

## Confirm the public interfaces and lifetime rules

Read these files in your **current** Framework checkout:

```text
framework/include/umicom/vcs/working_tree.h
framework/include/umicom/vcs/working_tree_review.h
framework/include/umicom/build/parser.h
framework/include/umicom/build/diagnostic.h
framework/include/umicom/diagnostics/compiler_parser.h
```

`UmiVcsWorkingTreeRead` returns an owned opaque observation. `UmiVcsWorkingTreeDescribe` copies a summary. `UmiVcsWorkingTreeDestroy` releases the observation. A source-control UI must copy any required data before destroying the observation; borrowed entry pointers cannot outlive it. The parser returns a `UmiStatus` and fills a caller-owned diagnostic only when it recognises a complete record.

## Optional SDK configuration on Windows

The standalone lab does **not** require the SDK. To build the optional example, supply a prefix that actually contains the installed Framework package configuration. The location below is illustrative; check your local installation first.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact-framework" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" `
    -DBTB_WITH_UMICOM_FRAMEWORK=ON -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact-framework" --parallel 2
```

If CMake cannot find `UmicomFrameworkConfig.cmake` or the imported targets, the optional integration is **not verified**. Do not work around the problem by compiling source under `framework/src/vcs/` into the educational application; that would break the single-owner architecture.

## Run the read-only consumer

```powershell
& ".\output\learning-build\change-impact-framework\btb-framework-readonly-example.exe" `
    "C:\umicom\Umicom-Applications"
```

The output should describe the actual checkout's branch, detached state, staged/untracked counts and dirty submodule counters. Another line contains the **fictional** compiler diagnostic that the public parser recognised. Finally the **real Framework Automated Build System** evaluates a fictional public-header change and lists the selected Framework, Studio and Trader scopes, demonstrating inherited impact with the existing native API. These are distinct sources: one is a live, read-only Framework observation; the other is a fixed testing string. Do not present either as test or release qualification evidence for the OS.

## Design discussion: where to place production impact analysis

If Umicom Studio and OS Control Centre both require real change-impact decisions, **reuse the Framework Automated Build System that already exists**; extend its existing C23 scope/plan contracts through an approved architectural change only if a genuinely missing capability has been demonstrated. The service should receive Framework-owned repository observations and actual target/test metadata. Application workbenches render the resulting plan and request approved operations; they do not own Git or test execution.

This update does **not** modify Framework or claim the optional consumer was built against your installed SDK. It illustrates the intended boundary. The owner must approve production changes after review of the current Framework modules to prevent overlapping implementations.

**Exercises:** Compare the `UmiVcsWorkingTreeSummary` fields with the textual `git status` output from your own checkout. Explain why `divergence_known == 0` cannot be treated as `ahead == 0 && behind == 0`. Draw the ownership arrows for a background worker, immutable observation, GTK4 view model and UI widget.

**Review questions:** What does `find_package(UmicomFramework CONFIG REQUIRED)` establish? Which CMake targets does the optional executable link? Who owns the returned tree? What would you record if the SDK is unavailable? Why must a derived impact plan not mutate Git?

**Next:** run positive, negative and deterministic mutation tests against the bounded C23 policy model.
