# Major Update 38 — Beginner-friendly merge, build, test and Git commands

**No Python or PowerShell script is created.** These are individual interactive PowerShell commands. The only new executable implementation is the C23 educational laboratory. Do not merge or delete the entire existing repository.

## Step 1 — Extract the review package

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-38-System-Administration-From-Zero.zip" -DestinationPath ".\Bits2Banking-Update38-Review" -Force
```

Open Beyond Compare and compare:

- **Left:** `C:\umicom\Bits2Banking-Update38-Review\Umicom-Bits2Banking`
- **Right:** `C:\umicom\Umicom-Bits2Banking`

Merge only the reviewed new files. Preserve existing authorship, C23 source, previous lessons, original books, illustrations and README files. The provided original user guide was copied unchanged.

## Step 2 — Inspect your current repository

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
```

Confirm the active branch is `main` and you are inside the intended project. If you see uncommitted unrelated changes, review and preserve them before continuing.

## Step 3 — Configure the native C23 laboratory

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sysadmin-readonly-text" -B ".\output\learning-build\sysadmin-readonly-text" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
```

**Expected:** CMake reports successful configure and generation. If the compiler cannot be found, verify the MSYS2 UCRT64 installation and command path before changing project files.

## Step 4 — Build the laboratory

```powershell
cmake --build ".\output\learning-build\sysadmin-readonly-text" --parallel 2
```

**Expected:** the build creates `btb-sysadmin-text.exe` and `btb-sysadmin-text-test.exe`. The exact build output is toolchain-dependent.

## Step 5 — Run the C23 tests

```powershell
ctest --test-dir ".\output\learning-build\sysadmin-readonly-text" --no-tests=error --output-on-failure
```

**Expected:** 10/10 registered tests pass when the toolchain and source build successfully. Report the actual Windows result rather than copying an expected count as validation.

## Step 6 — Inspect one safe sample file

```powershell
& ".\output\learning-build\sysadmin-readonly-text\btb-sysadmin-text.exe" ".\labs\native\sysadmin-readonly-text\fixtures\sample.md"
```

**Expected:** 26 bytes, 2 lines and a final newline for the checked-in fixture. The file is opened read-only and remains unchanged.

## Step 7 — Review navigation and website

Open `UPDATE_38_NAVIGATION_AND_REVIEW.md`. Merge the new top-level course section into your **current** `mkdocs.yml`, preserving every older entry. If the existing MkDocs environment is available:

```powershell
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes the existing MkDocs publisher. No new Python implementation is introduced. If the environment is absent, report the website build as NOT RUN; the standalone HTML course works without it.

## Step 8 — Standard Git workflow (only after review and tests)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add complete beginner system administration course"
git push origin main
git status
```

**Why these commands:** `git status` shows what changed, `git add -A` stages *all* tracked/untracked modifications and removals, `git diff --cached --check` checks whitespace, and `git diff --cached` shows the actual commit content. `git commit` records a local revision. `git push origin main` publishes reviewed local `main` commits. If the push is rejected or the checkout is detached, stop and inspect Git status/history instead of force-pushing.
