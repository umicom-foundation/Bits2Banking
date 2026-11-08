<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-filter-categories-and-open-dialogs.md

PURPOSE:
Share file-opening categories between applications

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Share file-opening categories between applications

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

## A filter is a browsing aid

An Open dialog can show a subset of filenames, such as C sources or hardware descriptions. A filter describes that subset. It does not validate contents, grant permission or install a toolchain.

Framework supplies default categories. The first five entries keep their existing positions; Programming Languages, Hardware Description Languages and Build Files follow them.

## Inspect the categories

1. Run the lab with cpu.vhd, app.dart, main.uc and CMakeLists.txt.
2. Read each name's Filter lines.
3. Notice that a file can match a specialised category and All Files.
4. Try cpu.vhd.backup. Its final suffix is backup, so the hardware filter does not match.
5. Try a path ending in a directory separator. It is rejected as a filename.

The helper supports all-files wildcards, suffix patterns such as *.vhd, and literal basenames such as CMakeLists.txt. It is not a complete shell-pattern interpreter. Arbitrary question marks or bracket expressions have no special meaning here.

## Follow the data into a GUI

The GTK adapter creates toolkit file filters from Framework descriptions. This is a presentation responsibility: it displays shared choices. The matching helper lets non-GUI consumers inspect the same description without opening a window.

Toolkit matching rules may differ from this helper's ASCII case handling. An adapter needs review on each supported platform, especially for uppercase suffixes. Keep All Files available for legitimate files outside specialised categories.

## Test observable behaviour

A UI test should open the chooser, observe categories, select a fixture and confirm that the document loader receives its path. A catalogue test alone cannot prove that a menu click opens the chooser.

Keep separate checks for command dispatch, chooser presentation, cancellation, accepted selection and document editing. A failure in each layer needs a diagnostic that identifies that layer.

## Practice

Propose a useful category with three patterns. Check each text capacity and the set's remaining capacity. Explain why the grouping helps a user. Add it through the shared description API rather than hard-coding a second filter implementation in an application.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Keep an object unchanged when an operation fails](language-filter-results-and-failure-atomicity.md) · [Next: Separate editing rules from compiler support](language-comments-syntax-and-build-tools.md)
