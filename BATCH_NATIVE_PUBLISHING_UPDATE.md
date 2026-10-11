# Native publishing update — build environment and volume cataloguing

The C23 educational tool builds from the Umicom Framework source under
`C:\umicom\Umicom-Applications\framework`. Bits2Banking holds the teaching
content, original books, website navigation and video scripts.

## 1. Review and merge

Compare the batch's two top-level folders against:

```text
C:\umicom\Umicom-Applications
C:\umicom\Umicom-Bits2Banking
```

Copy only the reviewed files into the matching folders. Existing source files
not listed in the delivery remain unchanged. Keep the source code's original
headers, licence, public names and comments. The earlier MkDocs renderer
implementation is retained in `site_renderer.c` inside a disabled review block.

## 2. Rebuild the C application

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
  -B ".\build\umicom-education" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON

if ($LASTEXITCODE -ne 0) { throw "Configure failed." }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Build failed." }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Tests failed." }
```

Five tests are registered: original path validation, original manuscript
publication, new book composition, new renderer/interpreter regression and
CLI help.

## 3. Fix the local MkDocs environment

The observed error was `C:\msys64\ucrt64\bin\python.exe: No module named mkdocs`.
That Python installation is separate from a normal Windows Python environment.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
py -3 -m venv .venv
if ($LASTEXITCODE -ne 0) { throw "Python virtual environment failed." }

& ".\.venv\Scripts\python.exe" -m pip install -r ".\requirements-docs.txt"
if ($LASTEXITCODE -ne 0) { throw "MkDocs installation failed." }

& ".\.venv\Scripts\python.exe" -m mkdocs --version
if ($LASTEXITCODE -ne 0) { throw "MkDocs is not installed in .venv." }
```

If `py` is not installed, use the full path to a compatible Windows Python
installation. The C tool does not install or modify Python for the user.

## 4. Build and start the website

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education doctor --repo $Books
if ($LASTEXITCODE -ne 0) { throw "Doctor found missing dependencies." }

& $Education verify --repo $Books
if ($LASTEXITCODE -ne 0) { throw "Site inputs are incomplete." }

& $Education build --repo $Books
if ($LASTEXITCODE -ne 0) { throw "MkDocs failed. Do not start the server." }

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`. Stop the listener with Ctrl+C.

For an explicit interpreter path:

```powershell
& $Education build --repo $Books `
  --python "C:\umicom\Umicom-Bits2Banking\.venv\Scripts\python.exe"
```

## 5. List and assemble the preserved Volume 1 manuscript

```powershell
& $Education book list --repo $Books
& $Education book assemble --repo $Books --volume islam_blueprint_for_life
```

The generated file is `output/native-books/islam_blueprint_for_life.md` inside
Bits2Banking. It is an intermediate Markdown manuscript, not the final
book. When inputs change, an existing different output remains untouched;
review the changes before requesting `--refresh`.

## 6. Validate the new website lessons

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m unittest discover `
  -s tests -p "test_native_books_and_renderer_docs.py" -v

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

## 7. Inspect commits and push separately

Framework first:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): recover MkDocs selection and add native book assembly"
git push origin main
```

Then record the Framework submodule revision in its parent:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record native education improvements"
git push origin main
```

Finally publish Bits2Banking:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "docs(education): teach native book publishing and website builds"
git push origin main
```

Verify `git status` and `git branch --show-current` before each commit. In the
Applications parent, changes to unrelated application submodules should not be
staged or committed as part of this update. Inspect `git diff --cached --stat`
and unstage anything not belonging to the approved work.

## Implementation boundaries

No existing BookForge, Pandoc, Python, PowerShell, original manuscript,
Framework web service or Kernel functionality is removed. `build` still uses
MkDocs; this batch improves Python-environment selection and accurate failure
reporting but does not implement a native replacement for all MkDocs features.
The web server is a read-only local development preview, not Internet hosting.
The existing Umicom CLI is unchanged; `umicom-education` remains a separate
program until the integration milestone is qualified.
