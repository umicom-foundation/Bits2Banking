# Major Update 08 — Windows merge, build, test and commit

## Review the update

The delivery archive has two top-level folders matching your workspace: `Umicom-Applications` and `Umicom-Bits2Banking`. Extract it into a new review directory and compare complete source files before merging.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-08-Native-C23-Learning-and-Audit.zip" -DestinationPath ".\Bits2Banking-Update08-Review" -Force
```

Use Beyond Compare to compare `C:\umicom\Bits2Banking-Update08-Review\Umicom-Applications\framework` with `C:\umicom\Umicom-Applications\framework`, and `C:\umicom\Bits2Banking-Update08-Review\Umicom-Bits2Banking` with `C:\umicom\Umicom-Bits2Banking`. Merge only the reviewed files. Do not replace whole repositories.

The changed Framework CLI and CMake files are complete source files, not patches. The update adds a native audit, not a second website renderer. None of the existing Framework functionality or historical book material should be removed.

## Framework: configure, build, test

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

Expected: eight tests, including `framework.education.navigation_audit`. Run the new test by itself if necessary:

```powershell
ctest --test-dir ".\build\umicom-education" -R "^framework\.education\.navigation_audit$" -V
```

## Audit and render Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education audit --repo $Books
```

Expected: a nonzero number of navigation pages and zero missing, duplicate, unsafe and structural issues. This is a **read-only, limited C23 navigation check**, not a complete YAML parser.

Only if the audit succeeds, build the real website with its existing renderer:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
Test-Path ".\site\index.html"
```

Python remains necessary for the existing MkDocs renderer; this update adds no new Python application source. The final `Test-Path` should print `True`. If strict MkDocs fails, retain the full output and fix its actual configuration or content error before starting the server.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`, review Volume 1 and the new lessons, then stop the server with Ctrl+C.

## Build and test the Arena Allocator laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\arena-allocator" `
    -B ".\output\learning-build\arena-allocator" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\arena-allocator" --parallel 2
ctest --test-dir ".\output\learning-build\arena-allocator" --output-on-failure
```

Expected: two tests pass.

## Build and test the bounded ledger-line laboratory

```powershell
cmake -S ".\labs\native\bounded-ledger-line" `
    -B ".\output\learning-build\bounded-ledger-line" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"

cmake --build ".\output\learning-build\bounded-ledger-line" --parallel 2
ctest --test-dir ".\output\learning-build\bounded-ledger-line" --output-on-failure
```

Expected: three tests pass, including the deterministic 20,000-input mutation check. All tests must be performed before committing.

## Commit Framework first

The Framework repository may be a Git submodule. Verify that it is on a **local `main` branch**, not a detached commit, and inspect its status.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): add native C23 navigation target audit"
git push origin main
```

Do not commit if the branch is detached or the staged changes contain unrelated work.

## Commit Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add native C23 memory and parsing courses"
git push origin main
```

## Commit Umicom Applications last

The parent repository records the updated Framework submodule commit. Stage that change alone; do not stage other application submodules unless they were explicitly part of this update.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current

git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record native education navigation audit"
git push origin main
```

If any command reports an error or there are no applicable staged changes, stop and inspect the repository status instead of generating an empty commit.
