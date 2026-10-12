# Major Update 31 — Merge, build, test, review and Git commands

**Update:** Advanced Git engineering, repository recovery and C23 Git ancestry.
**Only destination:** `C:\umicom\Umicom-Bits2Banking`.
**No new executable scripts:** All supplied source executables use C23. These are **interactive PowerShell commands**; nothing here creates a `.ps1` or `.py` file.

## Step 1 — Extract into a separate review directory

Download the ZIP into `C:\umicom`, then execute:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-31-Professional-Git-and-C23-History.zip" `
    -DestinationPath ".\Bits2Banking-Update31-Review" `
    -Force
```

Compare **left** `C:\umicom\Bits2Banking-Update31-Review\Umicom-Bits2Banking` with **right** `C:\umicom\Umicom-Bits2Banking` using Beyond Compare. Merge new files only. Do not delete the existing repository, replace entire directories or copy Build output into source control. This batch supplies **no existing-file replacements**.

The package contains an additive navigation recipe in `UPDATE_31_NAVIGATION_AND_REVIEW.md`. Merge reviewed entries into your actual `mkdocs.yml` only if all referenced lesson/video files from Updates 28–30 are present. Preserve all existing navigation, including the original *Islam: Blueprint for Life* volume. The recipe must not be applied twice.

## Step 2 — Set your UCRT64 compiler environment

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version
```

This reads installed tool versions. If a command is missing, correct the existing MSYS2 environment rather than writing an ad hoc setup script.

## Step 3 — Configure, build and test the new C23 lab

```powershell
cmake -S ".\labs\native\git-history" `
    -B ".\output\learning-build\git-history" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\git-history" --parallel 2

ctest --test-dir ".\output\learning-build\git-history" --output-on-failure
```

**Expected focused result: 11/11 tests passing.** If the build fails, do not claim Windows acceptance and do not commit a claimed successful integration.

Run the tutorial demonstration:

```powershell
& ".\output\learning-build\git-history\btb-git-history-demo.exe"
```

Expected message: local `main` at classroom ID 2 is behind `origin/main` at ID 4 even when detached HEAD is checked out at ID 4. No Git command is executed by this demonstration.

## Step 4 — Prior-work regression tests (where the prior lessons were merged)

```powershell
cmake -S ".\labs\native\work-handoff" -B ".\output\learning-build\work-handoff" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-handoff" --parallel 2
ctest --test-dir ".\output\learning-build\work-handoff" --output-on-failure
```

Expected Update 29 result: **5/5**.

```powershell
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\work-dispatch" --output-on-failure
```

Expected Update 30 result: **9/9**, provided `labs/native/completion-queue` exists and contains the earlier approved C23 library. These earlier tests are separate: they do not automatically run when you test `git-history`.

## Step 5 — Verify the existing website

After the navigation merge, run the Framework-owned native education audit **if your installed `umicom` tool provides it**. Use the real path to your built executable, not a guessed location. Then run the established MkDocs publishing tool:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes the **existing** MkDocs renderer; the batch does not create or deliver a Python implementation. If `.venv` or MkDocs does not exist, mark the publication gate as **not run**, do not claim it passed and report the missing dependency. Inspect missing targets and duplicate nav entries. The original historical volumes must remain available.

## Step 6 — Review staged changes and commit to `main`

Only after the new lab builds, the relevant regressions pass, the intended documentation is reviewed and the working branch is confirmed as `main`:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current

git add -A

git diff --cached --check
git diff --cached --stat
git diff --cached --name-status

git commit -m "feat(learning): add Git recovery lessons and native C23 history lab"

git push origin main

git status
```

**`git add -A` includes deletions** and any unrelated changes in the current repository. Inspect `git diff --cached --name-status` before the commit. Stop if you are detached, behind/diverged from the remote, if a push is rejected, or if staged paths do not match the reviewed batch. Use Chapter 192 for safe diagnosis. Do not force push.

## Step 7 — Verify downloaded ZIP integrity

```powershell
Get-FileHash `
    -LiteralPath "C:\umicom\Umicom-Bits2Banking-Update-31-Professional-Git-and-C23-History.zip" `
    -Algorithm SHA256
```

Compare the result to the SHA-256 text file supplied beside the ZIP. A hash match shows that the bytes match the supplied manifest; it is not cryptographic authentication of the publisher unless the manifest's origin is independently trusted.

## Source ownership

No changes to Umicom Framework, OS, Kernel, Applications, Studio or Trader are required for this learning batch. The educational DAG uses its own fixed graph because it teaches ancestry; real repository inspection, Git process handling, status parsing and gitlink staging must use the existing **Umicom Framework** C23 modules. Do not introduce application-local PowerShell/Python helpers to implement these behaviours.
