# 45. How a C program starts another program

When you click **Build** in an IDE, the IDE rarely compiles every language itself. It usually starts a compiler, build tool or package builder and waits for a result. A C program can perform the same operation. In Umicom Education, the C executable starts MkDocs to turn Markdown into HTML.

This lesson follows that process and explains why the selected executable, its arguments and its exit code matter.

## 1. A running program is a process

A *process* is an executing instance of a program. The operating system assigns it resources such as memory and handles to files or sockets. One process can ask the operating system to start another process.

In our example, `umicom-education` is the **parent process** and a Python interpreter running MkDocs is the **child process**. The parent waits while the child processes the site. When the child exits, the parent examines its result.

```text
PowerShell
    |
    v
umicom-education.exe      (native C23 parent)
    |
    | choose interpreter and pass arguments
    v
python.exe -m mkdocs ...  (child process)
    |
    v
site/index.html           (generated output)
```

The C web server is not part of this build process. It runs afterward and reads the generated files.

## 2. Arguments are values, not a shell command

The native source constructs an argument vector, conceptually like this:

```c
const char *arguments[] = {
    "python", "-m", "mkdocs", "build", "--strict",
    "--config-file", configuration,
    "--site-dir", destination,
    NULL
};
```

Each element is one argument. A repository path containing spaces stays a single argument; it is not split apart by a shell. This is safer than constructing one long text string and passing it to a shell for interpretation.

The actual updated implementation also handles the Windows Python launcher (`py -3`) and explicitly selected interpreters, so the vector is assembled using the chosen runtime.

## 3. Check capabilities, not just executable names

The original command selected the first `python` in `PATH`. On Windows with MSYS2 UCRT64, this can be `C:\msys64\ucrt64\bin\python.exe`. That interpreter may compile and run Python code correctly but may have no MkDocs installation.

The updated code checks whether the candidate environment contains both `mkdocs` and `material` before launching the actual build. It tries the project's `.venv` first. The purpose is not to prefer one Python brand over another: it is to find an environment that can perform the requested task.

The distinction applies to other build tools too. Finding `gcc.exe` does not prove the compiler supports a required target architecture; finding Java does not prove the right JDK is installed; finding a package manager does not prove a particular library is available.

## 4. Understand exit codes

By convention, a process that completes successfully returns exit code `0`. Nonzero results indicate that something failed or that the program rejected an operation.

The native command should not print **success** merely because it managed to launch Python. It waits for MkDocs, checks the exit code and then verifies that the expected `site/index.html` exists.

Read this part of the real source:

```text
Umicom-Applications/framework/src/education/site_renderer.c
```

Find `UmicomEducationBuildSiteWithPython`. Identify where the child is launched, where the exit status is checked and where the expected output file is verified.

## 5. Test failures without installing or breaking Python

The Framework build includes a small C program named `umicom-education-test-python`. It imitates the command-line behaviour needed by the tests. No Python package installation is required to run it.

The renderer regression test checks a successful child, a child that reports a build failure, a missing executable and a checkout-local environment that should take precedence over an unrelated interpreter.

This technique is called a *test double*: a controlled substitute for an external dependency. It allows the parent program's error-handling behaviour to be tested independently of the real service.

## 6. Exercise: trace one failed build

Run `umicom-education build` from a machine that already has the documentation dependencies installed. Record which Python executable is selected and check the generated `site/index.html`. Then read `site_renderer.c` and answer:

- Why is `-m mkdocs` preferable to assuming an unrelated `mkdocs.exe` on `PATH`?
- Which operation checks that both MkDocs and its theme are present?
- What should the parent return if the child exits with an error?
- Why does the C web server not automatically install missing packages?

Continue with [the lightweight C web-server lesson](39-build-a-c-web-server.md) to see how the generated website is delivered to a browser.
