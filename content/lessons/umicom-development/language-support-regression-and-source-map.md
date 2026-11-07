<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-support-regression-and-source-map.md

PURPOSE:
Trace language support from a command to an outcome

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Trace language support from a command to an outcome

This module starts with a small command-line program and follows its calls into Umicom Framework. Each lesson includes the setup needed to begin independently. You will inspect real source while learning how document names, memory boundaries and editing capabilities fit together.

A terminal is a window that runs written commands. PowerShell is one such terminal on Windows; Bash is common on Linux. A compiler translates C into a program your machine can run. CMake describes the build; Ninja performs the work. An SDK supplies the headers that describe a library and the compiled library files.

Install a C23-capable compiler, CMake and Ninja. Install the Umicom Framework SDK containing the document and editor components. These steps assume Windows tools in C:\msys64\ucrt64\bin and SDK files in C:\umicom\installed\framework; replace those paths if your installation differs. No GTK window or broker connection is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\framework-language-inspection"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
.\build\language-inspection.exe cpu.vhd app.zig CMakeLists.txt
```

On Linux, use the same lab from your checkout and your installed SDK:

```bash
cd ~/umicom/Umicom-Bits2Banking/labs/native/framework-language-inspection
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework"
cmake --build build
./build/language-inspection cpu.vhd app.zig CMakeLists.txt
```

Stop if configure or build reports an error. The first output line should be `cpu.vhd: vhdl`, followed by its choice, comment style and matching filters. This program examines the name only; the named files need not exist. [Learning C](../../courses/learning-c/index.html) and [Learning CMake](../../courses/learning-cmake/index.html) provide longer setup explanations.

## A feature needs an observable result

An Open button is useful when selecting a file produces an editable document. A language registry can be correct while that journey is broken. Test each boundary, then the complete path.

A regression test records expected behaviour so later changes reveal when it breaks. It is evidence about the scenario exercised, not proof that an entire application is complete.

## Map the source

| Framework-relative file | Responsibility |
| --- | --- |
| include/umicom/document/language_detection.h | Identity result and detection contract |
| src/document/language_detection.c | Bounded names and suffix mapping |
| include/umicom/document/languages.h | Public catalogue operations |
| src/document/languages.c | Choices and identity consistency |
| include/umicom/document/file_filter.h | Bounded filter descriptions |
| src/document/file_filter.c | Categories and matching |
| src/editor/comment_style.c | Shared line-comment profiles |
| adapters/gtk4/editor_gtk4.c | Presentation and syntax integration |
| tests/document/test_file_filter_boundaries.c | Invalid counts, strings, aliases and valid names |

Follow a declaration in include to its implementation in src, then a caller and test. This is a repeatable way to explore an unfamiliar library.

## Plan layered checks

1. Identity: cpu.vhd gives vhdl; an unknown suffix gives plain.
2. Catalogue: the selected ID matches its example filename's identity.
3. Bounds: full arrays and unterminated patterns are rejected without mutation.
4. Presentation: the chooser becomes visible after Open.
5. Lifecycle: selection loads text; cancellation preserves work.
6. Editing: type a character, switch tabs, return and confirm the change.
7. Persistence: save to a selected path and reopen the file.

Each step needs its own expected result. A skipped GUI test is not a pass.

## Run standalone checks

After building this lab:

```powershell
ctest --test-dir build --output-on-failure --no-tests=error
```

The lab contains two name-inspection checks. Record a result only after reading the actual output. Framework and Studio require their own configured builds and suites.

## Diagnose a failure

If this lab succeeds but Open does nothing, investigate dispatch and window ownership. If selection works but typing does not, inspect the active buffer and event handling. If compilation fails, preserve the diagnostic and source revision.

Write the smallest reproducible input and observed result. “Selecting cpu.vhd opens a buffer whose language is plain” is more actionable than “VHDL is broken.”

## Read the source

[Open the example source](../../../labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Separate editing rules from compiler support](language-comments-syntax-and-build-tools.md)
