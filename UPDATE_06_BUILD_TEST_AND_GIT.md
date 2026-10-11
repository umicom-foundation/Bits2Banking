# Major Update 06 — review, build, test and commit

The changes are delivered under **two repository folders**. Compare each folder with your local checkout in Beyond Compare before merging. Preserve historical documentation, comments, headers, API names and publishing workflows. This update does not delete or replace the existing Islam chapters or BookForge scripts.

## 1. Review the sources

Compare:

- Batch `Umicom-Applications/framework` with `C:\umicom\Umicom-Applications\framework`.
- Batch `Umicom-Bits2Banking` with `C:\umicom\Umicom-Bits2Banking`.

The Framework CLI accepts a new, explicit `serve --build` option. Without that option, `serve` remains read-only and expects already-generated HTML. The original `build` command has not changed.

## 2. Build and test Umicom Education (Windows PowerShell)

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

Expected: seven registered tests. They include `framework.education.renderer` and the new `framework.education.serve.preflight`. Do not claim the Windows batch is accepted until all tests pass on your machine.

## 3. Build and test the owned-notes laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\owned-notes" `
    -B ".\output\learning-build\owned-notes" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\owned-notes" --parallel 2
ctest --test-dir ".\output\learning-build\owned-notes" --output-on-failure
& ".\output\learning-build\owned-notes\bits2banking-owned-notes.exe"
```

## 4. Build and test checked arithmetic

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\checked-money" `
    -B ".\output\learning-build\checked-money" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\checked-money" --parallel 2
ctest --test-dir ".\output\learning-build\checked-money" --output-on-failure
& ".\output\learning-build\checked-money\bits2banking-checked-money.exe"
```

## 5. Validate the lessons and website

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Python = ".\.venv\Scripts\python.exe"

& $Python -m pytest -q -p no:cacheprovider ".\tests\test_update06_learning.py"
& $Python -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "Website build failed; review MkDocs diagnostics." }
Test-Path ".\site\index.html"
```

The expected last output is `True`. MkDocs remains the HTML renderer for this batch. A successful `doctor` check alone does not generate the website.

## 6. Start the native web preview

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`. Stop with Ctrl+C. To let the C utility run MkDocs immediately before starting the preview, use:

```powershell
& $Education serve --repo $Books --build --python $Python --port 8765
```

`--build` is not a Python replacement; it invokes the existing MkDocs process through the Framework-owned renderer adapter. If the build fails, the server does not start.

## 7. Review, commit and push — Framework first

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): add explicit site build preview and preflight tests"
git push origin main
```

Confirm `main` is checked out before committing. Stop if you see a detached HEAD or unrelated staged changes.

## 8. Commit and push — Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach memory ownership and checked arithmetic in C23"
git push origin main
```

## 9. Record the Framework revision — parent repository last

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record education preview and C23 learning updates"
git push origin main
```

This last commit records the Framework submodule revision without staging unrelated application-module changes. If there is no changed Framework reference, do not create an empty commit.
