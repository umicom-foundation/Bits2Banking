# 70. Check a learning website with a native C23 tool

The Bits2Banking website has two important parts: the lesson files in `content/` and a configuration file, `mkdocs.yml`, that tells MkDocs how to present them. A navigation entry can look correct to a reader while pointing to a Markdown file that does not exist.

We will use a small C23 command to check the **local Markdown targets** before asking MkDocs to render the website. This is useful even on a computer that does not have Python installed.

## 1. Identify the input

Consider these entries:

```yaml
nav:
  - Home: index.md
  - Learning:
      - "Memory in C23": lessons/03-native-code/67-pointers-and-borrowed-memory.md
```

The first entry points to `content/index.md`. The group heading, `Learning`, does not point to a file. The third entry points to a Markdown lesson under `content/lessons/`.

The file-extension and path checks are straightforward. Parsing **arbitrary YAML correctly is not**. A C tool that only examines navigation paths must not claim to validate every feature of YAML. MkDocs remains responsible for full configuration parsing and website rendering.

## 2. Inspect the native command

Open these files in Umicom Framework:

```text
include/umicom/education/nav_audit.h
src/education/nav_audit.c
tests/education/test_nav_audit.c
```

The implementation reads `mkdocs.yml`, extracts local `.md` navigation targets from the deliberately limited format used by the learning site, and checks that the files exist beneath `content/`.

It rejects duplicate targets, missing files, directory traversal such as `../README.md`, and platform-specific absolute paths. It reads only; it does not repair the configuration or overwrite lessons.

## 3. Build the Framework-owned tool

Open PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\tools\umicom-education" -B ".\build\umicom-education" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure
```

The tests include a deliberately missing Markdown page, a duplicate navigation target and a parent-directory traversal attempt. They expect each invalid case to be **detected**, not accepted.

## 4. Audit the learning site

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education audit --repo "C:\umicom\Umicom-Bits2Banking"
```

A clean result reports a count of navigation targets and zero missing, duplicate, unsafe or structural issues. The check is read-only. If a path is missing, inspect the corresponding line in `mkdocs.yml` and the actual file name. Do not delete or rename a historical chapter merely to silence a warning.

The native command does **not** guarantee that MkDocs YAML syntax is valid. After the audit, run the existing renderer:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

The Python interpreter is used here because the existing MkDocs publishing engine is still the canonical website renderer. The new audit itself is C23-only.

## 5. Make a controlled mistake

In a temporary copy of the repository, change one navigation target from `index.md` to `index-missing.md`. Re-run `audit`. It should identify a missing target without changing any source file. Restore the original navigation entry and confirm the error disappears.

Try adding the same `.md` path twice under different titles. The native audit should reject that duplicate because the same page has been listed twice. This check is independent of the prose displayed in the menu.

## 6. What to learn from the implementation

Look for the following concepts in `nav_audit.c`: bounded line buffers, avoiding unchecked path concatenation, exact suffix checks, recording previously seen paths, and reporting errors without rewriting inputs. These are general techniques that also apply to file importers and repository tools.

The next step is [Lesson 71: Compiler diagnostics and static analysis](71-compiler-diagnostics-and-static-analysis.md), where we use the compiler to inspect our C code before it becomes part of a project.
