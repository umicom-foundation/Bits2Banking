# 46. Diagnose a failing build tool

A compiler, documentation generator and website server are different programs. When one command fails, the useful first question is **which program failed and at what stage?** We will investigate the same failure that can occur while building the Bits to Banking website on Windows.

## 1. Recognise the tools involved

Our educational website starts as Markdown chapters in `C:\umicom\Umicom-Bits2Banking\content`. MkDocs converts them into HTML, CSS and other files under `site`. A separate C23 executable, `umicom-education.exe`, can then serve those files to a browser.

```text
Markdown chapters ──> Python + MkDocs ──> site/index.html
                                             |
                                             v
                                Umicom Education web server
                                             |
                                             v
                                    Web browser on your PC
```

There are three independent operations: **build the C program**, **generate the website** and **start the server**. Success at one stage does not automatically prove that the next stage works.

## 2. Confirm the native application works

Open PowerShell and start in the Umicom Applications directory:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

`cmake --build` asks Ninja to compile changed source files. `ctest` starts the native regression tests. Neither command installs MkDocs. When both pass, we know that the C code and the checked test cases built and ran; we have not yet proved the website renders.

If a test fails, read its name, executable and first error. A failing test is evidence that needs investigating, not a reason to delete the build directory.

## 3. Find the correct Python interpreter

A computer may have several independent Python installations. A package installed into one interpreter is not necessarily visible to another.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs --version
```

The output should identify MkDocs and a version. This is stronger evidence than running `python --version`, because the latter says nothing about installed packages.

To test both required Python modules without depending on the terminal's `python` alias, run:

```powershell
& ".\.venv\Scripts\python.exe" -c "__import__('mkdocs');__import__('material')"

if ($LASTEXITCODE -ne 0) {
    throw "MkDocs or MkDocs Material is unavailable in this environment."
}
```

Successful imports normally print nothing. If a module is missing, the exception names it. Install the documented website dependencies into **that same interpreter**:

```powershell
& ".\.venv\Scripts\python.exe" -m pip install -r ".\requirements-docs.txt"
```

We do not need to upgrade pip just because it prints an update notice; a notice is not a build failure.

## 4. Why a short Python expression matters on Windows

The native application launches Python as a child process. Its C source supplies a collection of arguments rather than executing a typed command through PowerShell.

A previous implementation passed this probe as an argument containing spaces:

```text
-c "import importlib.util,sys;sys.exit(...)"
```

On the reported MSYS2/Windows process boundary, Python received only `import`, which is not a complete Python statement. That produced:

```text
File "<string>", line 1
    import
          ^
SyntaxError: Expected one or more names after 'import'
```

This message did **not** prove that MkDocs was missing. It proved that the probe itself did not reach Python correctly.

The corrected probe uses a single argument without whitespace:

```c
"__import__('mkdocs');__import__('material')"
```

`__import__` is a Python built-in function that loads a named module. The semicolon separates two Python statements. The C program uses an argument array, not a shell command, so it does not ask the shell to interpret these characters. If either import fails, the Python child exits unsuccessfully and the native command reports that the chosen renderer cannot be used.

The corrected source is in `framework/src/education/site_renderer.c`. Examine `EducationRun` and `EducationSpawn` to see where each argument is constructed and where the operating system starts the child.

## 5. Render the website independently

First verify that MkDocs itself can generate the site. This bypasses the native launch wrapper and is a useful diagnostic comparison.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" -m mkdocs build --strict

if ($LASTEXITCODE -ne 0) {
    throw "MkDocs reported a site configuration or content error."
}

Test-Path ".\site\index.html"
```

The final command should print `True`. The `--strict` option turns MkDocs warnings into build failures; missing navigation pages or broken references therefore need correcting before the website is considered ready. Some external links cannot be validated offline.

If this direct build fails, solve the **MkDocs error** first. Changing the C web server will not repair malformed Markdown or navigation.

## 6. Build and serve through the native command

Return to the native application and use the same verified interpreter explicitly:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Education doctor --repo $Books --python $Python
& $Education build --repo $Books --python $Python

if ($LASTEXITCODE -ne 0) {
    throw "The website build did not succeed."
}

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` in your browser. Press **Ctrl+C** in the terminal when finished. The server binds to the local computer only; it is not a public Internet host.

## 7. Interpret the result

A good diagnosis identifies the failing boundary.

| Observation | What it means | What to check next |
| --- | --- | --- |
| CMake cannot compile | Native source or toolchain problem | First compiler diagnostic, include path, linker error |
| Native tests fail | A checked C behaviour differs from expectation | Failing CTest name and test output |
| MkDocs import fails | Python environment cannot load a module | Interpreter path and packages |
| MkDocs `build --strict` fails | Site configuration or content needs repair | First MkDocs warning or error |
| `site/index.html` is absent | No usable website home page exists | Build step before server launch |
| Browser cannot connect | Server did not start or port is unavailable | Server console output and local port |

## 8. Exercise

Write down the paths of your Umicom Education executable, project-local Python and generated site home page. Run `doctor`, `build` and `serve` in that order and record the exit status of each step. Change the port to a different unused value and explain which part of the system that changes. Do not edit any source files for this exercise.

**Next:** [Learn how CTest isolates process failures](47-test-child-processes-with-ctest.md).
