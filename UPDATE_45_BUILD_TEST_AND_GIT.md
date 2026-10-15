# Major Update 45 — Build, Test and Git: PowerShell 7 command reference

**Umicom Foundation · Bits2Banking · 15 October 2026 · UK English**

This is an **additive package for `C:\umicom\Umicom-Bits2Banking` only**. It does not edit Umicom Framework, Umicom-Applications, Umicom Kernel or Umicom OS. New executable code is ISO C23; PowerShell is used **only for commands typed by a human learner**. No new `.py`, `.ps1`, JavaScript or other scripting-language implementation files are provided.

## 1. Extract to a review directory

Save `Umicom-Bits2Banking-Update-45-Operational-Resilience-and-C23-Review.zip` under `C:\umicom`. Open PowerShell 7 and enter:

```powershell
Set-Location 'C:\umicom'
Expand-Archive -LiteralPath '.\Umicom-Bits2Banking-Update-45-Operational-Resilience-and-C23-Review.zip' -DestinationPath '.\Bits2Banking-Update45-Review' -Force
```

Compare using Beyond Compare:

- **Left (new material)**: `C:\umicom\Bits2Banking-Update45-Review\Umicom-Bits2Banking`
- **Right (existing repo)**: `C:\umicom\Umicom-Bits2Banking`

Merge only reviewed **new** files. Do **not** replace the repository, remove old chapters, change earlier lab logic or replace the original New Project Beginner Guide. The ZIP does not require deleting or replacing any existing file.

## 2. Prepare the compiler and verify prerequisites

The new C23 laboratory **imports the existing original Update 39–44 teaching libraries** through CMake. They must already exist in the checkout. If CMake reports a missing earlier lab, merge that earlier full batch; do not reconstruct it from a shortened code snippet.

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
Test-Path '.\labs\native\security-operations-review\CMakeLists.txt'
```

The final command should return `True`. The actual installed compiler version may differ from the Linux validation environment.

## 3. Configure, build and run tests

```powershell
cmake -S '.\labs\native\operational-resilience' `
    -B '.\output\learning-build\operational-resilience' `
    -G Ninja `
    -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' `
    -DBUILD_TESTING=ON

cmake --build '.\output\learning-build\operational-resilience' --parallel 2

ctest --test-dir '.\output\learning-build\operational-resilience' `
    --no-tests=error --output-on-failure
```

Expected from the complete original Update 39–45 teaching chain: **161/161 CTest cases** (131 existing + 30 new). Record the actual host outcome, not just the expectation. A partial merge must not be counted as a passing full regression run.

Run the safe executable:

```powershell
& '.\output\learning-build\operational-resilience\btb-operations-demo.exe'
```

The demo prints fictional `REVIEWABLE`, `BLOCKED`, calculated due time and `RESTORED_ONLY` outcomes. It cannot access or change real Windows services, SSH connections or backups.

For focused tests and test enumeration:

```powershell
ctest --test-dir '.\output\learning-build\operational-resilience' -N
ctest --test-dir '.\output\learning-build\operational-resilience' -R '^bits2banking\.operations\.' --no-tests=error --output-on-failure
```

Expected focused count: **30** (29 cases and the demo).

## 4. Review the new course and MkDocs navigation

Open `UPDATE_45_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html` directly in a browser. It contains 108 System Administration chapters, with **all 96 original chapter bodies preserved** and 12 Stage 8 chapters added. The standalone equivalent is available separately.

Open `UPDATE_45_MKDOCS_NAV_SNIPPET.yml` and the **current** repository `mkdocs.yml` side by side in Beyond Compare. Append the Stage 8, native engineering and video sections under the **existing** `nav:` key. Do not replace MkDocs configuration or remove *Islam: Blueprint for Life* or other historic books.

When the repository's existing publishing environment has MkDocs installed, execute:

```powershell
& '.\.venv\Scripts\python.exe' -m mkdocs build --strict
```

This invokes the **pre-existing MkDocs publishing tool**, not a newly delivered Python implementation. If the environment is missing, record `Not Run`. Validation of the additive navigation snippet alone is **not** proof that the complete MkDocs site builds successfully.

## 5. Git: add, commit and push to main

Only after reviewing the merged source, completing the relevant builds/tests and confirming `main` is checked out:

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'

git status

git branch --show-current

git add -A

git diff --cached --check

git diff --cached --stat

git diff --cached

git commit -m "feat(learning): add Stage 8 operations course and native C23 resilience review"

git push origin main

git status
```

**Critical:** `git add -A` stages **all** additions, modifications and deletions in the current repository. Inspect the staged diff and remove unrelated work from staging before committing. If the push is rejected, inspect `git fetch origin main`, the history difference and the working tree; do not force-push, hard-reset or clean away edits.

## 6. Windows-specific acceptance that remains outstanding

This package's new C23 source and previous regressions were tested using GCC/Clang on a Linux host. The Windows MSYS2/UCRT64 build, native toolchain compatibility and strict full-site MkDocs build still require separate testing on your own computer. No verification report should claim these have passed until actual evidence exists.
