<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/language-names-and-document-identity.md

PURPOSE:
Identify a document from its filename

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Identify a document from its filename

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

## What this lesson builds

A document is a piece of work an editor keeps open. Its language identity tells other components which editing rules may apply. The identity is a short stable name, such as c or vhdl. It is different from the filename and the text inside the document.

The lab prints an identity without opening a file. This separation is useful: a file picker can describe a candidate before a document loader reads it.

## Follow one name through the program

1. Open the lab's main.c in a text editor.
2. Find main. The operating system supplies argc, the number of command arguments, and argv, an array of pointers to their text. argv[0] names the program. The loop begins at 1 so it examines only names supplied after the executable.
3. Find Inspect. Its filename parameter points at one name. The const qualifier says this function must not change those characters through that pointer.
4. Locate umi_document_language_detect. It writes a UmiDocumentLanguageIdentity through the address passed as its second argument.
5. Read the status check before printf. A status is a result code. UMI_STATUS_OK means this operation completed; the caller must not treat other values as success.

The ampersand in &identity obtains identity's address. The detector needs that address to fill in the object owned by Inspect. A dot accesses a field inside an object. The format %s prints a terminated character string.

## Experiment

Run with main.c, cpu.vhd and report.unknown as three arguments. Expect c, vhdl and plain respectively. Create no files. Change report.unknown to report.c and run again: the identity changes even though no contents were examined.

An extension is a useful hint, not proof that a file contains valid C. A parser must check its contents before compilation.

## Check your understanding

Why is plain useful? It lets an editor display unfamiliar text without inventing language-specific behaviour. Why does Inspect keep identity on its stack? The small result belongs to this call and is needed only until the function returns. It is not returned as a pointer to a local variable.

If a build cannot find an SDK header, check the installed SDK path. Changing the example filename cannot resolve a missing build dependency.

## Read the source

[Open the example source](../../../labs/native/framework-language-inspection/main.c).

## Continue learning

[Course contents](../../courses/umicom-development/index.html) · [Next: Read a shared language catalogue safely](language-catalogues-and-borrowed-data.md)
