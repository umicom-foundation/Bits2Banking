# Bits2Banking — Update 21: Build, test and Git guide

This update changes **only** `C:\umicom\Umicom-Bits2Banking`. It does not replace or edit Umicom Framework, Umicom Applications, Umicom Kernel or Umicom OS.

## 1. Review and merge

Download `Umicom-Bits2Banking-Update-21-Filesystems-Journalling-and-Recovery.zip` into `C:\umicom`. Open PowerShell and run:

```powershell
Set-Location "C:\umicom"

Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-21-Filesystems-Journalling-and-Recovery.zip" `
    -DestinationPath ".\Bits2Banking-Update21-Review" `
    -Force
```

In Beyond Compare, compare the source directory:

```text
C:\umicom\Bits2Banking-Update21-Review\Umicom-Bits2Banking
```

against the destination:

```text
C:\umicom\Umicom-Bits2Banking
```

Review every complete replacement before merging. `mkdocs.yml` contains a complete copy of the previous Update 20 configuration plus new navigation entries. **Preserve any newer local additions** when resolving the comparison; never replace the repository root wholesale.

## 2. Check the development tools

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

& "C:\msys64\ucrt64\bin\gcc.exe" --version
cmake --version
ninja --version
ctest --version
```

The C23 tests do not require Python. MkDocs and its Python environment are still required for generating the website; this batch introduces no Python scripts.

## 3. Compile the write-back sector laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\writeback-sector-store" `
    -B ".\output\learning-build\writeback-sector-store" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "Block-store configure failed" }

cmake --build ".\output\learning-build\writeback-sector-store" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Block-store compilation failed" }

ctest --test-dir ".\output\learning-build\writeback-sector-store" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Block-store tests failed" }

& ".\output\learning-build\writeback-sector-store\btb-sector-store-demo.exe"
if ($LASTEXITCODE -ne 0) { throw "Block-store demonstration failed" }
```

**Expected:** 2/2 CTest checks pass. The demo shows a blank stable sector before flush, then the Notes text after flush and a simulated restart.

## 4. Compile the journalled Notes laboratory

This laboratory reuses `block_store.c` from the preceding laboratory. No separate installed library is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\journalled-notes" `
    -B ".\output\learning-build\journalled-notes" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "Notes journal configure failed" }

cmake --build ".\output\learning-build\journalled-notes" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Notes journal compilation failed" }

ctest --test-dir ".\output\learning-build\journalled-notes" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Notes journal tests failed" }

& ".\output\learning-build\journalled-notes\btb-journalled-notes-demo.exe"
if ($LASTEXITCODE -ne 0) { throw "Notes journal demonstration failed" }
```

**Expected:** 2/2 CTest checks pass. The demonstration recovers a note at revision 1 after an interrupted save, using the stable journal record.

## 5. Check MkDocs and the complete website

Build using the existing repository-local Python interpreter:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs website build failed" }

Test-Path ".\site\index.html"
```

The last command should return `True`. If MkDocs fails on a missing file or navigation entry, inspect the relevant path before committing; do not delete historical chapters to silence the warning.

After building, preview the website using the **existing** Framework-owned native C server if it is available on your machine:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education serve --repo $Books --port 8765
```

Open the loopback URL `http://127.0.0.1:8765/`. No Framework build or code modification is needed for this batch. This command uses the already-installed local native server; if the executable is not present, first review your existing Framework checkout separately rather than changing it as part of Update 21.

## 6. Check the lesson links and diagrams

In the website navigation confirm that lessons 132, 133, 134, 135 and 136 open, and that scripts 44 and 45 link to the matching chapters. Review that the original *Volume 1 — Islam: Blueprint for Life* chapters still appear in their established order.

The new diagrams reside under `content/assets/diagrams/`. They are editable SVG files; no fonts are bundled. The Kernel source references are read-only GitHub links.

## 7. Commit to GitHub (Bits2Banking only)

After the CTests and website review succeed, run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status

git branch --show-current

git add -A

git diff --cached --check

git diff --cached --stat

git commit -m "feat(learning): teach filesystems durable writes and C23 journal recovery"

git push origin main

git status
```

Confirm that the active branch is `main`. `git add -A` stages all changes in Bits2Banking, including any unrelated edits; review the staged files before committing. No other repository should be staged or pushed for this update.

## 8. Problems to investigate

A CMake error before compilation normally indicates a compiler path or generator issue. A compiler error points to a specific C line: fix the source, then rebuild incrementally without deleting the build folder. A failed CTest identifies a behaviour contract; do not remove the failing test. A MkDocs strict failure means the website is not yet ready to publish. Retain the actual warning and error output so it can be reproduced.

Remember that the storage model deliberately simulates power-loss recovery. A successful test does **not** prove actual host-disk persistence after sudden power loss.
