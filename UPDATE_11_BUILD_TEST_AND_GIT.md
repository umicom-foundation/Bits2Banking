# Update 11 — Build, Test, Preview and Publish

## 1. Merge the files into your existing checkouts

Extract the distribution ZIP to a temporary directory. Compare its `Umicom-Applications/framework` folder with `C:\umicom\Umicom-Applications\framework` and its `Umicom-Bits2Banking` folder with `C:\umicom\Umicom-Bits2Banking`. Review the replacement source files before merging. Do not replace the complete repositories, delete existing book inputs, or copy previous build products into source control.

## 2. Configure the Framework Education build

In PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
  -B ".\build\umicom-education" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "Framework Education configure failed" }
```

## 3. Build and test

```powershell
cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Framework Education build failed" }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Framework Education tests failed" }
```

**Expected total:** 14 passing tests. The previous 12 tests remain and two new tests are added: `framework.education.elf_symbols` and `framework.education.symbols.cli`.

Inspect the new cases separately:

```powershell
ctest --test-dir ".\build\umicom-education" `
  -R "^framework\.education\.(elf_symbols|symbols\.cli)$" `
  -V
```

The test first writes the synthetic ELF fixture, then checks CLI inspection of that file under a directory containing spaces. It also tests ELF32 big-endian metadata, malformed sections, overlong offsets and 12,000 deterministic mutations. The CTest fixture dependency works even when selecting only the CLI test.

## 4. Inspect the test ELF object

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"

& $Education symbols --file `
  ".\build\umicom-education\education-elf-test\fixture with spaces\umicom example.o"
```

Expected summary includes `Format: ELF64`, `Symbols: 2`, `Defined: 1`, `Undefined: 1`, and `Relocations: 1`. The sample contains the labels `umicom_export` and `umicom_missing`. This synthetic fixture is intentionally independent of the Windows compiler's native COFF format.

## 5. Build the C23/Assembly linker laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\linker-relocations" `
  -B ".\output\learning-build\linker-relocations" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Linker lab configure failed" }

cmake --build ".\output\learning-build\linker-relocations" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Linker lab build failed" }

ctest --test-dir ".\output\learning-build\linker-relocations" `
  --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Linker lab tests failed" }
```

**Expected:** two passing tests. The demo prints `Bits2Banking learning path: 21 lessons` (a fictional example, not a count of published chapters).

## 6. Build and preview the educational website

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Python -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs strict build failed" }

Test-Path "$Books\site\index.html"
```

The last command should return `True`. The current publishing pipeline uses MkDocs through the existing Python virtual environment; this update does not replace MkDocs.

Run the Framework-owned native C web server in a separate PowerShell session:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and check the five new chapters, both video scripts and the original Islam volume. Stop the server with Ctrl+C. The native server is a local-only preview; do not expose it to the public internet.

## 7. Review and commit Framework first

**Do not commit if a repository is detached or if the tests fail.** Verify `main` and review the complete staged changes; `git add -A` includes unrelated untracked and deleted files.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"

git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(education): inspect ELF symbols and relocations in C23"
git push origin main
```

## 8. Commit Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(learning): teach linker symbols and kernel memory layout"
git push origin main
```

## 9. Update the parent Umicom Applications repository last

After pushing Framework's updated revision, record its new submodule commit in the parent:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

git status
git branch --show-current

git add framework
git diff --cached --check
git diff --cached --stat

git commit -m "chore(framework): record native ELF education inspection"
git push origin main
```

Only the `framework` submodule pointer should be staged in this parent step, unless a separately reviewed repository-lock file legitimately needs updating. Do not include unrelated application-submodule modifications. Run `git status` in each repository after pushing.

## 10. What to report if a check fails

Copy the complete output of the failing `cmake`, `ctest` or MkDocs command and the result of `git status` in the affected repository. Do not delete build directories or overwrite source code merely to make an error disappear. A failed strict website build should be fixed before committing the site navigation changes.
