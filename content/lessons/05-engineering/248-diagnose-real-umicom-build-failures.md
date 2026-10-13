# Chapter 248 — Diagnose real Umicom build failures without losing code

**Bits to Banking · Engineering track · Umicom Foundation**  
**Primary language:** C23 · **Tools:** Git, CMake, Ninja, CTest  
**Prerequisites:** Chapters 240–247, safe source-preservation practices.

## Why this matters

A failed Umicom build may contain thousands of successful compilation lines and one small but decisive failure. The temptation is to delete unfamiliar code, remove a test, replace an entire CMake file or “simplify” a module until the compiler stops complaining. That can produce a misleading green build at the cost of losing functionality. The correct objective is **understand the first failing operation and preserve existing behaviour while repairing the defect**.

## Stage 1: establish provenance

Record the root and Framework revisions, current branches, working-tree state and build preset before attempting a fix:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git rev-parse HEAD
git -C ".\framework" rev-parse HEAD
git -C ".\framework" status --short
cmake --list-presets
```

A submodule in detached HEAD is not necessarily broken. A dirty Framework means you must preserve and review the changes before replacing any file. `git add -A` is an eventual staging command, not a repair tool.

## Stage 2: identify the first actual failure

Run one reproducible build command, using the configured preset:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --build --preset windows-ucrt64-all-debug --parallel 2
```

Read from the **first `FAILED:` target**. A missing include means something different from a conflicting prototype or unresolved symbol. For each finding, write down the object target, source file, command, diagnostic and process exit status. The source path might live in Framework while the failing consumer lives in Studio or Bank; distinguish the module that defines the missing symbol from the module that calls it.

If the error is C23 syntax or type compatibility, inspect the declaration and implementation **together**. If it is a link failure, examine target-level CMake dependencies and duplicate exported names. If it is a test failure, identify the named test and inspect its expected ownership or state transition. Do not hide the failing test behind `--exclude-regex` just to obtain a green summary.

## Stage 3: repair at the authoritative boundary

Suppose an Umicom Studio GTK4 view calls a Framework-owned diagnostic API. The fix belongs in Framework if the public contract or reusable implementation is wrong. It belongs in the Studio adapter only if the adapter misuses the correct Framework API. Avoid adding a second private parser or local workaround that will drift.

When refactoring, preserve author and licence headers, public names, comments, feature behaviour and existing implementation logic. If an old code path genuinely becomes inactive, retain it in a documented disabled block until reviewed, rather than silently deleting it. Make the smallest behaviour-preserving change that addresses the actual defect.

## Stage 4: re-run the exact failed target and the broader suite

After repairing the failure, rebuild the relevant target and then the full selected build. Use CTest with failure output to verify that tests executed rather than merely being registered:

```powershell
cmake --build --preset windows-ucrt64-all-debug --parallel 2
ctest --preset windows-ucrt64-all-debug --output-on-failure
```

Some failure classes require runtime launch acceptance that unit tests cannot cover. For example, a GTK4 executable that starts only while MSYS2 is on PATH is not yet an independently installable Windows application. Record packaging and double-click verification separately.

## Stage 5: stage, review, publish

Only after the build and tests have been reviewed should you stage the intended changes:

```powershell
git status
git add -A
git diff --cached --check
git diff --cached --stat
```

Inspect the staged changes carefully; `git add -A` can stage unrelated edits and deletions. For multi-repository changes, commit Framework on its `main` first, then rebuild and publish each consumer's pinned Framework gitlink. Never push a parent gitlink to a child commit that other developers cannot fetch.

## Incident exercise

Create an incident note containing: observed failure, authoritative owner, expected source revision, CMake preset, reproduction command, first actual failing command, proposed minimal repair, preserved source, test outcomes, and any unverified platform gates. Compare this note with the C23 evidence snapshot in Chapter 245: one describes human diagnosis; the other stores typed evidence. They complement rather than replace each other.

**Assessment:** Why can deleting a failing test be a false repair? It hides the evidence instead of fixing behaviour. What is the first action after encountering a dirty submodule? Preserve and inspect the edits before updating. Who authorises physical deletion of superseded Umicom functionality? The project owner after explicit review.

**Next:** Chapter 249 shows the SDK-backed adapter that passes Framework observations into the teaching model.
