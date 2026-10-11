# Update 03 — Renderer reliability and book-source checks

The native C23 website command now checks MkDocs and Material without passing a whitespace-containing Python probe across the Windows process boundary. The renderer test double verifies the exact child argument and reports failures without a fatal assertion. The new read-only `book check` operation validates one source volume before manuscript assembly.

## Update the two repositories

Merge the batch folders into their matching local paths:

- `Umicom-Applications/framework/` → `C:\umicom\Umicom-Applications\framework\`
- `Umicom-Bits2Banking/` → `C:\umicom\Umicom-Bits2Banking\`

Use a comparison tool and inspect complete replacement files. The batch does not modify the Framework's main `umicom` executable or the Umicom Kernel/OS repositories.

## Build and test the native executable

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Education configuration failed." }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Education compilation failed." }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Education tests failed." }
```

The renderer test no longer aborts on a failed assertion. To inspect it in detail:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.renderer$" -V
```

## Confirm the installed renderer

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs --version
& ".\.venv\Scripts\python.exe" -c "__import__('mkdocs');__import__('material')"
if ($LASTEXITCODE -ne 0) { throw "Python modules are not importable." }
```

You do not need to reinstall Python or recreate `.venv` when these commands succeed. A pip update notice is informational, not a failure.

## Build and start the website

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Education doctor --repo $Books --python $Python
if ($LASTEXITCODE -ne 0) { throw "Renderer preflight failed." }

& $Education build --repo $Books --python $Python
if ($LASTEXITCODE -ne 0) { throw "Website build failed." }

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and stop the preview with Ctrl+C. If MkDocs reports site-content errors, run it directly from the book checkout to see the error without the C wrapper:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

The preview is loopback-only and read-only. The existing Python-based MkDocs publishing engine remains in use; the native command does not install packages.

## Check and assemble an existing book

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& $Education book list --repo $Books
& $Education book check --repo $Books --volume islam_blueprint_for_life
if ($LASTEXITCODE -ne 0) { throw "Book source check failed." }
& $Education book assemble --repo $Books --volume islam_blueprint_for_life
```

`book check` makes no changes to `dropzone/documents`, `output/native-books` or the public website. `book assemble` writes a review manuscript in `output/native-books` and preserves a different previous manuscript unless `--refresh` is supplied deliberately.

## Review and publish

Run status and staged-diff checks before committing. Commit Framework first, then record its updated submodule revision in Umicom Applications, and then commit Bits2Banking independently. The normal CMake/Ninja build is incremental; do not delete the build directory.

## Next milestone

The next phase will consolidate MkDocs and BookForge publication so GitHub Pages has one deployment owner. It will validate historical Islam volume paths, existing book downloads, Umicom branding, navigation and the new learning pages before deployment. This update does **not** replace or disable any existing publishing workflow.
