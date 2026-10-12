# Major Update 30 — PowerShell build, test, review and Git instructions

**The code in this ZIP is C23 only.** The commands below are for use directly in a PowerShell terminal; this update adds no `.ps1`, `.py` or other automation script. Before beginning, confirm that `labs/native/work-handoff` and `labs/native/completion-queue` already exist in your local Bits2Banking repository.

## 1. Extract into a review folder; preserve the main checkout

Place the ZIP in `C:\umicom`. Then:

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-30-C23-Dispatch-and-Advanced-Git-Lessons.zip" -DestinationPath ".\Bits2Banking-Update30-Review" -Force
```

Open Beyond Compare. Compare **left** `C:\umicom\Bits2Banking-Update30-Review\Umicom-Bits2Banking` with **right** `C:\umicom\Umicom-Bits2Banking`. Merge only reviewed additions. Do not replace the entire repository. No existing code files are overwritten by this batch.

## 2. Verify the required previous native components

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
Test-Path ".\labs\native\work-handoff\handoff.c"
Test-Path ".\labs\native\work-handoff\handoff.h"
Test-Path ".\labs\native\completion-queue\queue.c"
Test-Path ".\labs\native\completion-queue\queue.h"
```

All four results must be `True`. Otherwise merge the missing earlier batch or check your repository root before proceeding; **do not** create duplicate queue files merely to satisfy the build.

## 3. Configure, build and test the native C23 dispatch lab

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

gcc --version
cmake --version
ninja --version

cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\work-dispatch" --output-on-failure
& ".\output\learning-build\work-dispatch\btb-work-dispatch-demo.exe"
```

Expected: **9/9 dispatch CTest cases passing** and the demonstration's final `PASS (3/3 delivered)` line. Stop on a compilation or test failure; do not commit a failed batch. The lab is self-contained **only after** the two existing libraries are present.

## 4. Re-run the previous native suites

```powershell
cmake -S ".\labs\native\work-handoff" -B ".\output\learning-build\work-handoff" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-handoff" --parallel 2
ctest --test-dir ".\output\learning-build\work-handoff" --output-on-failure

cmake -S ".\labs\native\completion-queue" -B ".\output\learning-build\completion-queue" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\completion-queue" --parallel 2
ctest --test-dir ".\output\learning-build\completion-queue" --output-on-failure
```

The previous Update 29 lab defines five tests; the earlier completion-queue lab defines two. These are **separate suites**, not part of the nine new tests. Test the Update 28 HTTP server independently using its existing build directory and documentation if that is part of your acceptance baseline.

## 5. Register the learning pages in MkDocs — reviewed edit

Read **`UPDATE_30_NAVIGATION_AND_REVIEW.md`**. Insert its documented YAML entries into your **current** `mkdocs.yml`, not a stale replacement. This update includes registration of **Chapters 167–190** and **Videos 58–65**, because earlier Update 28/29 material is still absent from the currently known navigation. Add the links from the new learning-path file to your existing course index if desired. Inspect with Beyond Compare before accepting the edit.

Validate the site using the already-installed publishing environment:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\mkdocs.exe" build --strict
```

This invokes an existing MkDocs executable; no Python application or script file is authored by this batch. If no environment exists, report publication **not run** rather than claiming success. The Framework-owned C23 education audit can provide an additional read-only navigation check if available in your installed toolchain.

## 6. Inspect the working tree and commit only Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git rev-parse --show-toplevel
git branch --show-current
git status
git diff --check
git diff --stat

git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached

git commit -m "feat(learning): add C23 dispatch and advanced Git workshops"
git push origin main
git status
```

Before `git add -A`, check for unrelated modifications and secrets; if present, stage only the intended paths. Confirm `main` is the active branch and inspect the staged patch. If `git push` is rejected as non-fast-forward, follow Chapters 184–186; do not force-push.

## 7. Publication and platform acceptance

The native lab was tested on Linux using GCC and Clang with sanitizers; **Windows UCRT64, full HTTP regression, strict MkDocs build and GitHub Pages acceptance remain for you to run locally**. Record your actual results and commit hash. No Framework, Applications, Kernel or OS repository requires modification for this Bits2Banking-only update.
