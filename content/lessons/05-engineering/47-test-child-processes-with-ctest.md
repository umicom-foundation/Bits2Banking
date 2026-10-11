# 47. Test child processes with CTest

A program can be correct when run once and still fail when another program launches it. An argument may be split into two values, an environment variable may be missing, or a child process may return an unexpected exit code. We can test these boundaries without repeatedly installing Python packages.

## 1. Understand a command-line argument

Consider this PowerShell command:

```powershell
python -m mkdocs build --strict
```

The program name is `python`. The values following it are arguments:

| Position | Value | Purpose |
| --- | --- | --- |
| 0 | `python` | Executable name |
| 1 | `-m` | Run a Python module |
| 2 | `mkdocs` | Module to run |
| 3 | `build` | MkDocs operation |
| 4 | `--strict` | Treat website warnings as errors |

In C, a similar program receives `int argc` (the number of arguments) and `char **argv` (an array of strings). On Windows, the operating system launches a command line and the child's runtime reconstructs `argv`; careless quoting can change the resulting values. On Unix-like systems, `exec`-family calls normally transfer the argument array directly.

The Umicom C23 website tool uses `_spawnvp` on Windows and `posix_spawnp` on POSIX systems. Both calls wait for a result through their respective platform mechanisms.

## 2. Why a test double is useful

The real Python installation is useful for integration testing, but it is inconvenient for testing every possible failure. Installing and uninstalling MkDocs to simulate a missing module would change the developer's environment.

Instead, Umicom Framework includes an executable named `umicom-education-test-python`. It is written in C and pretends to be the small subset of Python that the renderer needs. This kind of substitute is called a **test double**.

The test double accepts a renderer probe, checks its exact argument and either returns success or a failure code. For a requested website build, it creates a tiny `index.html` in the directory supplied by the test.

The two important source files are:

```text
framework/tests/education/mock_python.c
framework/tests/education/test_renderer.c
```

Find the `main` function in both files. Follow the value of `argv[2]` into the mock process and compare it with the expected probe.

## 3. A simple process-boundary test

The renderer probe is now a short Python expression:

```c
const char expected[] = "__import__('mkdocs');__import__('material')";
```

The mock checks that **exactly three arguments** arrive when the program name is counted. The executable path is `argv[0]`, `-c` is `argv[1]`, and the complete expression must be `argv[2]`.

If a Windows C runtime splits the expression unexpectedly, the mock prints the arguments it actually received and returns a nonzero exit status. The test does not need a working MkDocs installation to detect this problem.

## 4. Report failures without aborting

The old regression test used `assert(...)` for each expectation. Assertions are convenient during development, but a failed assertion may terminate a Windows executable abruptly with a runtime exception such as `0xc0000409`.

A test can be easier to diagnose when it prints the failed expectation and exits in a controlled way. The active renderer test uses a small `EDUCATION_CHECK` macro that prints the source file, line number and failing condition before returning a normal failure exit code.

This is a testing choice, not a replacement for error handling in a production application. Production code must validate its inputs and handle failures even when assertions are disabled.

## 5. Build and run the tests

From PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

The renderer test has several cases: an exact interpreter, a repository-local interpreter, a child that reports build failure, a missing renderer, an executable that does not exist and an executable path containing spaces. The test must return a nonzero status if one of these cases fails.

To run only the renderer test and show its output:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.renderer$" `
    -V
```

CTest's `-R` selects tests by regular expression. The `-V` option prints verbose output from the selected test, including the subprocess diagnostics. If the test fails, read its first `[FAIL]` line.

## 6. Distinguish unit and integration testing

A unit test can exercise a function without opening a real browser. A process-boundary test checks arguments and exit status using a controlled child executable. A full integration test launches the real Python interpreter, renders MkDocs, starts the C web server and downloads the resulting page.

These tests are complementary. The mock tells us whether the C program constructed and supervised its child correctly. Only the real website build tells us whether the installed MkDocs plugins and all source documents are compatible.

## 7. Exercise

Open `mock_python.c`. Find the branch controlled by `UMICOM_EDUCATION_TEST_NO_RENDERER`. Explain what the mock returns when the flag is present and why the parent must not proceed with a build.

Then open `test_renderer.c` and find the case that tests a path containing spaces. Explain why such a path is more realistic than assuming every developer uses a directory without spaces.

**Next:** [Validate a book before publishing](48-validate-a-book-before-publishing.md).
