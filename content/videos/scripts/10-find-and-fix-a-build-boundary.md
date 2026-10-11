# Find and fix a failing build boundary

**Run time:** Approximately 12–15 minutes.  
**Related lessons:** [Diagnose a failing build tool](../../lessons/05-engineering/46-diagnose-a-failing-build-tool.md) and [Test child processes with CTest](../../lessons/05-engineering/47-test-child-processes-with-ctest.md).

## 00:00–01:30 — Three separate programs

**Narration**

A website appears simple in a browser, but behind it there are several separate programs doing different jobs. We write the lessons in Markdown. MkDocs converts the Markdown into HTML. A native C program serves the resulting files over HTTP. The browser displays what it receives.

When the browser shows nothing, a good engineer does not immediately rewrite the server. We first find which stage has not completed. Has the C application compiled? Has MkDocs generated `index.html`? Is the server listening on the expected address?

**On screen**

Show the flow: Markdown → MkDocs → `site/index.html` → C server → browser. Display the two local repositories, `Umicom-Applications` and `Umicom-Bits2Banking`.

## 01:30–03:30 — Build the native program

**Narration**

Open PowerShell in `C:\umicom\Umicom-Applications`. First run the incremental native build. Then run CTest. If all tests pass, it tells us the C program and its test cases have run successfully. It does not prove that the separate website renderer works, because that renderer needs Python packages of its own.

**On screen: PowerShell**

```powershell
Set-Location "C:\umicom\Umicom-Applications"
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

**Narration**

Notice that the compiler does not need to install Python and that CTest does not automatically build the website. Each tool has a limited responsibility. That makes it easier to find and repair a failure.

## 03:30–06:00 — Find the interpreter that has MkDocs

**Narration**

Windows can have more than one Python installation. If the MSYS2 compiler directory is at the beginning of `PATH`, typing `python` may select the MSYS2 Python rather than the virtual environment for our website.

We will remove that ambiguity by naming the interpreter we want to test. The executable under `.venv\Scripts` has the packages installed for this project. Ask it to run MkDocs and report its version. Then ask it to import the two modules we need: MkDocs and Material.

**On screen: PowerShell**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs --version
& ".\.venv\Scripts\python.exe" -c "__import__('mkdocs');__import__('material')"
```

**Narration**

The import check normally prints nothing when it succeeds. If it fails, read the exact missing module. We can install dependencies into this environment without modifying the MSYS2 toolchain Python.

**On screen:** Show the `requirements-docs.txt` file and the interpreter's path.

## 06:00–08:45 — Why one missing space can break a build

**Narration**

The native C application starts Python and supplies an array of arguments. One argument is a Python expression that checks for the required modules. In the earlier Windows build, that expression contained spaces, and it reached Python as only the word `import`.

Python correctly rejected the incomplete statement, but the C application interpreted the error as a missing MkDocs installation. That is a classic example of a failure crossing between two separate programs: the software was present, but the arguments did not arrive as intended.

**On screen**

Open `framework/src/education/site_renderer.c` and locate `EducationRun`. Highlight the disabled original probe and then the active whitespace-free probe. Do not edit the source during this demonstration.

```c
"__import__('mkdocs');__import__('material')"
```

**Narration**

We keep the old implementation in a disabled section with a comment explaining why it was replaced. The history of the mistake is useful for education and future code reviews.

## 08:45–10:30 — Reproduce the boundary with a test double

**Narration**

We do not need to uninstall MkDocs just to check whether the C process handles missing modules. The source includes a second C program that acts as a small substitute for Python. It accepts the renderer's expected arguments and checks that the complete probe arrives as one string.

If the child receives the wrong arguments, the mock explains exactly what it saw and fails. If the parent cannot start a child or the child reports an error, the parent must report failure rather than pretend that the website was built.

**On screen: PowerShell**

```powershell
ctest --test-dir "C:\umicom\Umicom-Applications\build\umicom-education" `
    -R "^framework\.education\.renderer$" -V
```

**Narration**

The test also checks paths containing spaces. Real project directories are not always as simple as our example path. A good process launcher must not rely on every person choosing a directory with no spaces.

## 10:30–12:45 — Build and view the real website

**Narration**

Now that we understand the failing boundary, we can build the actual website. First, run MkDocs directly. This separates website-content problems from native subprocess problems. If MkDocs succeeds, we can run the native build and then start the C web server.

**On screen: PowerShell**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict

Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education build --repo $Books --python "$Books\.venv\Scripts\python.exe"
& $Education serve --repo $Books --port 8765
```

**Narration**

Open the browser at `http://127.0.0.1:8765/`. The website should now show its home page. If any command fails, stop there and read its diagnostics rather than continuing to the next step.

## 12:45–14:00 — What we learned

**Narration**

We have seen why software engineering is more than writing an individual function. A useful system depends on contracts between processes, command-line arguments, environments, exit codes, tests, generated files and network services. When we identify each boundary, complicated failures become easier to investigate.

The next lesson explains how to inspect and verify book source files before publication. The source code, CTest fixture and written lessons are available in the Umicom Foundation repositories. If you discover another failure or improve an explanation, share a tested change and help the next learner.

**On screen:** Display [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking), [Umicom Framework](https://github.com/umicom-foundation/umicom-framework) and the related lessons.
