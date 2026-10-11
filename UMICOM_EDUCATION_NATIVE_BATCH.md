# Native education tools and practical systems lessons

The Umicom Framework and Bits2Banking source files in this update use the same local repository directory structure as the Umicom development workspace.

The native C23 `umicom-education` application belongs to `Umicom-Applications/framework`, with a standalone qualifying build at `tools/umicom-education`. Its reusable services are in `include/umicom/education` and `src/education`. Bits2Banking owns the course pages, roadmap, video scripts and labs. No existing BookForge source, author manuscript or former tool is deleted.

## Windows: compile and test the Framework-owned tool

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" -B ".\build\umicom-education" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Umicom Education configure failed" }
cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Umicom Education build failed" }
ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Umicom Education tests failed" }
```

## Windows: build and preview the website

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = "C:\umicom\Umicom-Applications\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education doctor --repo $Books
& $Education prepare --repo $Books
& $Education verify --repo $Books
& $Education build --repo $Books
& $Education serve --repo $Books --port 8765
```

Stop the server with Ctrl+C, and inspect its status and any error output. The `build` command deliberately invokes the existing MkDocs renderer; it requires Python, MkDocs and the packages already specified in `requirements-docs.txt`. Install them in your selected Python environment if needed:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
python -m pip install -r ".\requirements-docs.txt"
python ".\tools\validate_learning.py"
python -m pytest -q -p no:cacheprovider ".\tests\test_learning_site.py" ".\tests\test_islam_volume_and_brand.py"
```

The old Python validation and BookForge routes remain the reference checks until native parity has been demonstrated. The C `verify` command checks expected source and published assets; it does not yet parse all Markdown links or render the book formats.

## Windows: compile the two independent exercises

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\safe-notes" -B ".\build\safe-notes" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\safe-notes" --parallel 2
ctest --test-dir ".\build\safe-notes" --output-on-failure

cmake -S ".\labs\native\http-header-scanner" -B ".\build\http-header-scanner" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\http-header-scanner" --parallel 2
ctest --test-dir ".\build\http-header-scanner" --output-on-failure
```

The `build/.gitignore` file excludes local compiled artifacts from Git staging.

## Compare and commit

Compare the `Umicom-Applications` and `Umicom-Bits2Banking` folders in the delivered ZIP with the matching local checkout folders. Merge the complete files after reviewing their headers and existing content. Do not replace the entire checkout or overwrite existing manuscripts. Commit source first in the Framework submodule, then publish the parent `Umicom-Applications` submodule revision. Commit Bits2Banking separately.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git add -A
git diff --cached --check
git commit -m "feat(education): add C23 learning-site tools and safe preview"
git push origin main

Set-Location "C:\umicom\Umicom-Applications"
git status
git add -A
git diff --cached --check
git commit -m "chore(framework): record native education tool revision"
git push origin main

Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git add -A
git diff --cached --check
git commit -m "docs(education): expand systems courses, roadmap and native labs"
git push origin main
```

Only commit repositories containing the intended changes. Review `git diff --cached --stat` and ensure no generated output, personal files or credentials have been staged. Keep GitHub publication workflows unchanged until the site/book pipeline is merged under one deployment owner.
