<!--
Umicom Bits2Banking
File: content/lessons/learning-c/30-link-with-a-native-sdk.md

PURPOSE:
Link a program with an existing native SDK

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Link a program with an existing native SDK

Follow one real C program through its build stages. Every stage produces a different kind of file; understanding those files makes errors easier to locate.

## Start here

A compiler turns source text into another representation. An executable is a file the operating system can start. A terminal lets you run tools by typing their names. This lab starts with supplied source; no earlier course is required.

Use a text editor, a C23-capable GCC, CMake 3.26 or newer and Ninja. On Windows these commands use the MSYS2 UCRT64 tools in C:/msys64/ucrt64/bin. Open PowerShell and type:

~~~powershell
Set-Location "C:/umicom/Umicom-Bits2Banking/labs/native/c-build-stages"
$env:Path = "C:/msys64/ucrt64/bin;" + $env:Path
gcc --version
~~~

On Linux or another Bash environment, change to your checkout's labs/native/c-build-stages directory and run gcc --version. The commands below use forward slashes accepted by GCC on both hosts. Create the output directory once with New-Item -ItemType Directory -Force out in PowerShell, or mkdir -p out in Bash. Stop when a command reports an error.

Linking needs a matching Umicom C SDK installed at C:/umicom/installed/umicom-c on Windows, or a prefix you choose on Linux. The lab README explains that one-time preparation. Preprocessing and compiling main.c do not need the SDK. [Learning C](../../courses/learning-c/index.html) provides a slower introduction to values and functions.

## What the linker combines

The linker combines object files and libraries into a final output. A static library is an archive of object files. In this lab, runner.o calls the Umicom C compiler, which in turn uses the shared runtime. These dependencies already exist; the lab supplies only a small caller.

After compiling both objects, run:

~~~text
gcc out/main.o out/runner.o -L"C:/umicom/installed/umicom-c/lib" -lumicom_c_compiler -lumicom_c_runtime -o out/stage-program.exe
~~~

Replace the SDK directory on Linux and omit .exe if you prefer. -L adds a library search directory. -l supplies a library name using the toolchain's naming rules. In this GCC static-link example, callers appear before the archives that satisfy their references.

Run the output and expect Value: 42. A successful link proves symbol resolution for that output, not that every input is handled correctly. Run the supplied boundary test through CTest as well.

## Prefer recorded target dependencies

The CMake version uses find_package(UmicomC CONFIG REQUIRED) and UmicomC::Compiler. The imported target records include paths and transitive link dependencies. It is more reliable than repeating machine-specific archive paths in every consumer.

1. Open CMakeLists.txt.
2. Find the runner library target.
3. Follow its dependency to UmicomC::Compiler.
4. Follow the executable's dependency back to the runner.
5. Compare that graph with the manual command above.

## Diagnose rather than guess

If a header is missing, check include paths and SDK installation. If a library is missing, inspect the prefix's library directory. If symbols remain unresolved, confirm the actual archive and target dependency. If formats are incompatible, compare compiler target, processor architecture and runtime; renaming the archive cannot repair incompatibility.

## Exercise

Draw three boxes: executable, teaching runner and Umicom C compiler/runtime. Mark which files you own and which engine is reused. This is how an application can build against a compatible installed Framework SDK without rebuilding the whole Framework on every edit.

## Read the source

[Open the example source](../../../labs/native/c-build-stages/CMakeLists.txt).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Understand object files and unresolved symbols](29-object-files-and-symbols.md) · [Next: Read diagnostics at the stage that produced them](31-read-diagnostics-by-stage.md)
