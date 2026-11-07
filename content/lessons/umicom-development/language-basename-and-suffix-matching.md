<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-basename-and-suffix-matching.md

PURPOSE:
Separate a filename from its directories

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate a filename from its directories

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

## Paths contain more than filenames

A path tells a program where something is located. In folder/example.c, folder is a directory and example.c is the basename, the final component. Windows commonly uses backslashes; Unix-style paths use forward slashes. The Framework detector recognises both when examining a name.

The suffix after the final dot often identifies a language. Searching the entire path for a dot is insufficient: a directory may contain a dot while the final filename has none.

## Trace the shared implementation

Open Framework's src/document/language_detection.c.

1. Locate the bounded scan that measures input up to UMI_PATH_CAPACITY.
2. Follow the loop that updates base after each directory separator.
3. Inspect special-name handling for CMakeLists.txt and Makefile.
4. Find strrchr(base, '.'). It searches the basename, not an earlier directory.
5. Read the exact-match loops before the case-insensitive fallback.

The order matters. The exact suffix .C selects C++, while .c selects C in this registry. Folding both to lower case before the exact match would lose that distinction.

## Run a table of examples

Use the names folder.with.dot/readme, main.C, main.c, cpu.SV and CMakeLists.txt. Expected identities are plain, cpp, c, systemverilog and cmake. Quote an argument that contains spaces so the terminal passes it as one name.

Draw two columns before running: input and predicted identity. Compare each prediction with the first output line for that name. Remaining lines describe the catalogue, comment profile and filters.

## Extend a mapping carefully

A proposed suffix needs a language ID and a regression example. Ask whether it is ambiguous in your project. The .v suffix is used here for Verilog; a project using another language with that suffix needs an explicit language selection or project policy.

Keep policy in a reusable Framework service. Unknown suffixes remain plain. A name ending in a separator is not a usable file selection and the file-filter matcher rejects it.

## Troubleshooting

If a known ID appears but colours do not, investigate installed syntax descriptions. If compilation fails, inspect the selected build tool and diagnostics. Neither problem is established by suffix mapping alone.

## Read the source

[Open the example source](../../../labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Previous: Read a shared language catalogue safely](language-catalogues-and-borrowed-data.md) · [Next: Bound a character buffer before reading it](language-filters-and-bounded-c-strings.md)
