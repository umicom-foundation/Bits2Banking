# 43. Prepare a reliable website build environment

A website begins as source files. In Bits to Banking, the lessons are Markdown files, the illustrations are SVG and PNG images, and `mkdocs.yml` describes how the pages are arranged. MkDocs turns those inputs into HTML files that a browser can display.

The **website builder** and the **web server** are separate programs. Building creates the files in `site/`. Serving reads those files and responds to browser requests. You can compile a web server perfectly and still have nothing to serve if the website builder is unavailable.

## 1. Understand what failed

Suppose `umicom-education build` prints:

```text
C:\msys64\ucrt64\bin\python.exe: No module named mkdocs
```

This is not a socket error or a C compiler error. The command started Python, but **that installation of Python** did not have the `mkdocs` package. Python packages are installed into particular Python environments; installing a package for one interpreter does not install it for every interpreter on the computer.

On a Windows development machine, the MSYS2 UCRT64 directory is often placed at the beginning of `PATH` so that GCC, CMake, Ninja and their dependencies are easy to find. It contains its own Python interpreter, which may not be the Python you usually use for documentation.

A *virtual environment* is a separate directory containing a Python interpreter and its project dependencies. We will use one for the Bits to Banking website, without changing the C toolchain.

## 2. Check the repository and Python installations

Open **PowerShell**:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status

Get-Command python -All

py -3 --version
```

`Get-Command` shows every `python` PowerShell can find. If `py -3` is unavailable, use an installed Python executable by its full path for the next step. Do not remove the MSYS2 compiler directory from `PATH` merely to solve a documentation problem.

## 3. Create the project's virtual environment

Run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

py -3 -m venv .venv
```

This creates the `.venv` directory in the educational repository. The project's `.gitignore` already excludes `.venv`, so installed packages will not be staged for Git.

Check the exact interpreter:

```powershell
& ".\.venv\Scripts\python.exe" --version
```

The filename is deliberately explicit. You do not have to activate a virtual environment or alter the system-wide `PATH`.

## 4. Install the site renderer

The repository includes `requirements-docs.txt`, which lists its documentation dependencies.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m pip install `
    -r ".\requirements-docs.txt"

if ($LASTEXITCODE -ne 0) { throw "Documentation dependency installation failed." }
```

Now ask that *same* Python environment whether MkDocs is available:

```powershell
& ".\.venv\Scripts\python.exe" -m mkdocs --version
```

A working installation prints the MkDocs version. A package installation can fail because of network access, package-index settings or permissions; resolve that failure before trying to build the site.

## 5. Build and inspect the website

First, build the source with MkDocs itself. This separates any Markdown errors from the C command-line wrapper:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict

if ($LASTEXITCODE -ne 0) { throw "MkDocs reported a build error." }

Test-Path ".\site\index.html"
```

The last command should return `True`. If strict mode reports a missing file, check the path mentioned in `mkdocs.yml` against the real `content/` directory. Do not delete a chapter or remove the *Islam: Blueprint for Life* navigation entry simply to silence the error: find the original manuscript or correct the reference.

## 6. Build with the native Umicom command

The new C23 command first checks whether an interpreter has both **MkDocs** and **Material for MkDocs**. It prefers `Umicom-Bits2Banking/.venv` and avoids selecting an unrelated MSYS2 Python merely because it appears first on `PATH`.

```powershell
Set-Location "C:\umicom\Umicom-Applications"

$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education doctor --repo $Books
& $Education build --repo $Books

if ($LASTEXITCODE -ne 0) { throw "The learning website was not built." }
```

You can also select the interpreter explicitly:

```powershell
& $Education build --repo $Books `
    --python "C:\umicom\Umicom-Bits2Banking\.venv\Scripts\python.exe"
```

The C program does not install Python or run `pip` for you. It selects a capable interpreter and passes a fixed, validated set of arguments to MkDocs. That keeps dependency installation a separate, deliberate action.

## 7. Start the local C web server

Only continue after the `build` command succeeds:

```powershell
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` in a browser. You should see the Bits to Banking home page, with links to the learning modules and the original Islam volume. Press **Ctrl+C** in the server terminal to stop it.

This is a read-only local preview. The server does not listen on your network interface, accept uploads or provide public HTTPS hosting.

## 8. Common errors and what they mean

| Message | What to check |
| --- | --- |
| `No module named mkdocs` | The selected Python does not have MkDocs. Use `.venv/Scripts/python.exe` and install `requirements-docs.txt`. |
| `No usable Python environment with MkDocs and MkDocs Material` | MkDocs and the theme are not available together in a discovered interpreter. |
| `MkDocs failed (child exit code ...)` | MkDocs started but rejected an input, theme, configuration or linked page. Read its first diagnostic. |
| `website home page is missing` | No successful site build produced `site/index.html`, or the wrong site folder was selected. |
| `Cannot bind 127.0.0.1:8765` | Another program may already be using that port. Stop it or select another unused port. |

## 9. Linux equivalent

From your Bits to Banking checkout:

```bash
cd "$HOME/umicom/Umicom-Bits2Banking"
python3 -m venv .venv
./.venv/bin/python -m pip install -r requirements-docs.txt
./.venv/bin/python -m mkdocs build --strict
```

The same compiled `umicom-education` application can select this environment without activation. Linux may need its distribution's `python3-venv` package before creating the virtual environment.

## 10. Try it yourself

Open a new PowerShell session and run `Get-Command python -All`. Next, compare the output of `python -m mkdocs --version` with `.\.venv\Scripts\python.exe -m mkdocs --version` from the book checkout. Explain why the two results may differ. Finally, verify that both the MkDocs command and the native `umicom-education` command build the same site destination.

Continue with [assembling a book using a C23 program](44-native-book-manuscripts.md).
