# Major Update 37 — Review, Build, Test and Git (PowerShell commands only)

**Audience:** Umicom maintainers merging the course; beginner learners should use the safe home-directory exercises, not commit into shared repositories without authorisation. **Policy:** native implementation in C23/Assembly first; PowerShell command snippets are interactive instructions, never `.ps1` implementations.

## 1. Extract for comparison (do not overwrite the working repository)

Save `Umicom-Bits2Banking-Update-37-Absolute-Beginner-Sysadmin-PowerShell-Git-C23.zip` in `C:\umicom`. Open PowerShell 7:

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-37-Absolute-Beginner-Sysadmin-PowerShell-Git-C23.zip" -DestinationPath ".\Bits2Banking-Update37-Review" -Force
```

**Beyond Compare left:** `C:\umicom\Bits2Banking-Update37-Review\Umicom-Bits2Banking`  
**Beyond Compare right:** `C:\umicom\Umicom-Bits2Banking`

Merge reviewed **additions only**. Do not replace the complete repository or delete existing files. The downloaded ZIP contains a single top-level `Umicom-Bits2Banking/` folder. Review the additive MkDocs fragment before modifying your local navigation.

## 2. Configure native GCC C23 lab

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\contributor-notes" `
    -B ".\output\learning-build\contributor-notes" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
```

A PowerShell backtick continues the command to the next line; no trailing spaces may follow the backtick.

## 3. Build, test and run

```powershell
cmake --build ".\output\learning-build\contributor-notes" --parallel 2
ctest --test-dir ".\output\learning-build\contributor-notes" --no-tests=error --output-on-failure
& ".\output\learning-build\contributor-notes\btb-contributor-notes-demo.exe"
```

**Default expected:** 8 registered tests, all 8 passing after an actual successful run. Do not mark `Not Run`, skipped or unexecuted tests as passed. The optional Framework SDK test is not part of the default eight.

## 4. Review the offline browser course

Open the additional self-contained `UPDATE_37_BEGINNER_COURSE_OFFLINE.html` directly in Edge, Firefox or another modern browser. It includes all 20 numbered lessons, the Windows PowerShell screenshot and inline diagrams without requiring a running website. Verify the Contents navigation, readable command blocks and print view. The separate same-content download can be shared with learners who have not yet installed Git.

## 5. Full course publication checks

After **manual** reviewed navigation integration:

```powershell
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This calls an existing MkDocs publishing runtime; Update 37 delivers **zero** new Python or PowerShell scripts. Verify the new course pages, the preserved legacy content and the original Islam volume. If MkDocs or the required Python virtual environment is absent, report the website gate as **not run**, not passed.

## 6. Standard reviewed Git sequence (Bits2Banking only)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git diff
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add absolute beginner sysadmin GitHub and C23 course"
git push origin main
git status
```

Confirm your branch is `main`, every staged path is intended, and the build/test evidence is satisfactory **before** committing. `git add -A` stages all current repository changes, including deletions. If the remote rejects your push as non-fast-forward, fetch and review divergence; never force-push to bypass it.

## 7. Explicit repository boundary

**This batch changes only `Umicom-Bits2Banking`.** No Framework, Applications, OS, or Kernel source is supplied. If in the future a reusable native repository capability is needed, implement it under Umicom Framework with project-owner approval and commit Framework first; do not create a PowerShell replacement.
