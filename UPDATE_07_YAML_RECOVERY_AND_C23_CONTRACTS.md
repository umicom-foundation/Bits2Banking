# Update 07 — Website Configuration Recovery and Safer C23 Contracts

## Changes in this delivery

This update is confined to **`C:\umicom\Umicom-Bits2Banking`**. The previously failing Framework renderer, CTest suite and Umicom C web server are left unchanged because the latest Windows report shows **7/7 native tests passed**. Both previous Notes and checked-money laboratories passed 1/1.

The current website failure occurs earlier: MkDocs cannot parse the locally merged `mkdocs.yml`, reporting lines 65 and 78. No HTML home page is generated, so the native web server correctly refuses to start. The complete MkDocs file in this update has been rechecked as YAML and retains every originally selected Islam volume chapter in its established order. The user's exact local file was not supplied for diff analysis, so an incorrect indentation or merge inconsistency is the most likely explanation rather than a confirmed single-byte cause.

## Included improvements

- Complete replacement `mkdocs.yml`, with existing site identity, palette, plugins, Islam volume, the 62 previously numbered chapters, video links, new chapters 63–66 and new scripts 16–17.
- `tools/check_mkdocs_config.py`: non-mutating YAML syntax and navigation checker, with line-level diagnostics and duplicate-key detection. The checker requires PyYAML, explicitly included in `requirements-docs.txt`.
- Six automatic regression tests that reproduce bad indentation, missing pages, duplicate navigation and the original Islam chapter order.
- A validation gate in both website GitHub Actions workflows before a publication build proceeds.
- Four fully illustrated, task-based chapters covering YAML repair, allocation failure injection, bounded HTTP byte handling and deterministic malformed-input testing.
- Two C23 laboratories with CMake/CTest, one allocator-failure test and one HTTP parser with unit and seeded-input tests.
- Two educational video scripts and two editable SVG diagrams.
- Updated course and laboratory indexes; appended roadmap checkpoint.

There are no deletions, no Framework code replacements, and no changes to original `dropzone/documents` manuscripts or historical book generators.

## Merge the patch

Extract the ZIP into a review directory, then compare the **`Umicom-Bits2Banking`** folder with the existing checkout using Beyond Compare. The full `mkdocs.yml` is the intended replacement for the locally broken file. Review the workflow files and append-only curriculum index changes against your actual checkout before accepting them.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-07-YAML-Recovery-and-Safer-C23.zip" `
  -DestinationPath ".\Bits2Banking-Update07-Review" -Force
```

Compare left `C:\umicom\Bits2Banking-Update07-Review\Umicom-Bits2Banking` with right `C:\umicom\Umicom-Bits2Banking`. To preserve the locally broken YAML for investigation, place a copy **outside** the Git checkout, for example in the review directory.

## Check syntax, navigation and the website

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Python = ".\.venv\Scripts\python.exe"
& $Python ".\tools\check_mkdocs_config.py" --syntax-only
if ($LASTEXITCODE -ne 0) { throw "Invalid YAML: correct mkdocs.yml." }
& $Python ".\tools\check_mkdocs_config.py"
if ($LASTEXITCODE -ne 0) { throw "Missing or duplicate chapter navigation." }
& $Python -m pytest -q -p no:cacheprovider ".\tests\test_mkdocs_config07.py"
if ($LASTEXITCODE -ne 0) { throw "Navigation tests failed." }
& $Python ".\tools\validate_learning.py"
if ($LASTEXITCODE -ne 0) { throw "A learning content link is invalid." }
& $Python -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "The full MkDocs site did not build." }
Test-Path ".\site\index.html"
```

`Test-Path` should return `True`. If navigation checking reports an original book chapter missing, run the existing preparation tool, then retry. Do not make placeholder chapters in the actual repository.

## C23 laboratory builds

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\fault-injection" -B ".\output\learning-build\fault-injection" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\fault-injection" --parallel 2
ctest --test-dir ".\output\learning-build\fault-injection" --output-on-failure

cmake -S ".\labs\native\http-byte-parser" -B ".\output\learning-build\http-byte-parser" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\http-byte-parser" --parallel 2
ctest --test-dir ".\output\learning-build\http-byte-parser" --output-on-failure
```

Expected newly registered tests: one allocator failure test and two HTTP tests. These are separate from the seven existing Framework education tests, which do not require rebuilding for this website-only source update.

## Start the existing native C server

Once the build has produced `site/index.html`:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education serve --repo "C:\umicom\Umicom-Bits2Banking" --port 8765
```

Open `http://127.0.0.1:8765/` and verify computing chapters and the original Islam volume. Stop with Ctrl+C.

## Commit (Bits2Banking repository only)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "fix(education): repair MkDocs navigation and add safer C23 contracts"
git push origin main
```

Do not push if `mkdocs build --strict` fails; provide its exact output for investigation. No Framework or parent Applications submodule commit is required by this update.

## Verification boundary

The delivered YAML has been parsed by PyYAML, the configured Markdown nav has been checked against a cumulative copy of the previous learning batches, and both C23 laboratories have been built and tested with Linux GCC and Clang plus ASan/UBSan. A validation fixture used **placeholder copies only for ten historical manuscript pages and for already prepared binary book/branding assets**; none are included in this ZIP. The complete MkDocs renderer was unavailable in the container, so actual Windows HTML generation and the live GitHub Pages workflow still require verification on the user's machine.
