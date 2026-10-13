# Major Update 33 — Windows merge, C23 build, tests and Git

**Project:** Bits to Banking · **Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Scope:** `C:\umicom\Umicom-Bits2Banking` only. Commands below are **interactive PowerShell commands**, not a PowerShell script. No new `.ps1` or `.py` project files are introduced.

## 1. Extract into a review directory

Download the ZIP to `C:\umicom`. Use a new review directory so the existing repository cannot be overwritten accidentally:

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-33-Framework-Git-Evidence-and-C23-Timeline.zip" -DestinationPath ".\Bits2Banking-Update33-Review" -Force
Get-FileHash -Algorithm SHA256 ".\Umicom-Bits2Banking-Update-33-Framework-Git-Evidence-and-C23-Timeline.zip"
```

Compare:

- Left: `C:\umicom\Bits2Banking-Update33-Review\Umicom-Bits2Banking`
- Right: `C:\umicom\Umicom-Bits2Banking`

Use Beyond Compare to copy **reviewed new files only**. Do not mirror the extracted partial package over the whole repository. `UPDATE_33_FILE_MANIFEST_SHA256.txt` lists every file and its SHA-256. No file already in the repository is intentionally replaced or deleted by this batch.

## 2. Configure the native C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-timeline" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
```

Check the CMake output for missing Update 32 release-gate source. That source is an optional prior-lab dependency, not part of this ZIP; if missing, the composition test is honestly NOT REGISTERED.

## 3. Build and run tests

```powershell
cmake --build ".\output\learning-build\git-review-timeline" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-timeline" --output-on-failure
ctest --test-dir ".\output\learning-build\git-review-timeline" -N
& ".\output\learning-build\git-review-timeline\btb-git-review-demo.exe"
```

**Expected:** 29 named C23 tests without the previous Update 32 gate source, or **30** with that source. The total includes the demonstration and, conditionally, the cross-batch release-gate composition regression. Both are native. The `mutation-100k` case tests 100,000 deterministic observations without network or background threads.

## 4. Optional Framework public-header compile check

Use only if a local Framework checkout exists and is at a revision you intend to work with:

```powershell
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-framework" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON -DBTB_FRAMEWORK_SOURCE_ROOT="C:\umicom\Umicom-Applications\framework"
cmake --build ".\output\learning-build\git-review-framework" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-framework" --output-on-failure
```

This builds a **compile-only adapter object target** against the Framework public header. It is *not* a linked live Framework VCS integration. That latter acceptance is deliberately not claimed here. Do not duplicate the existing Framework Git provider or create production application-local Git services.

## 5. Documentation publication check

Manually add navigation entries from `UPDATE_33_NAVIGATION_AND_REVIEW.md` to the current `mkdocs.yml`, preserving all existing entries. If navigation from Updates 28–32 is missing, review and merge those earlier additions too. No new Python scripts are needed; the established MkDocs tool still powers the existing website.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes **an existing site-build tool**; the delivered implementation is C23. If the virtual environment or MkDocs is unavailable, record this acceptance step as **NOT RUN** rather than assuming a pass.

## 6. Verify and commit Bits2Banking only

Before staging, inspect current branch and working-tree changes. Confirm every change belongs to this educational update and that tests passed. The project policy is to commit directly to `main` with no new branch.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Framework Git evidence and native C23 observation timeline"
git push origin main
git status
```

`git add -A` stages **all** additions, modifications and deletions in the current repository. If the staged diff contains an unexpected deletion or unrelated change, stop and review before committing. A rejected push requires ancestry inspection; never force-push as an automatic remedy.

**No Framework, Umicom Applications, Kernel or Umicom OS commit is required**: this package does not change those repositories.
