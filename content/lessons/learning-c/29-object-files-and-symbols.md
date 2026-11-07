<!--
Umicom Bits2Banking
File: content/lessons/learning-c/29-object-files-and-symbols.md

PURPOSE:
Understand object files and unresolved symbols

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand object files and unresolved symbols

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

## A compiled piece of a program

An object file contains compiled code and data plus information needed to combine it with other objects. It is normally not a complete application. A symbol names something such as a function or object that the toolchain must resolve.

Compile main.c without linking:

~~~text
gcc -std=c23 -Wall -Wextra -Wpedantic -c main.c -o out/main.o
~~~

This can succeed although LessonEvaluate is defined in another file. The compiler has its declaration from runner.h and can generate a reference that the linker will resolve later.

If your GCC toolchain includes nm, inspect the symbols:

~~~text
nm out/main.o
~~~

The spelling and decoration vary by platform. Look for a defined main and an unresolved reference corresponding to LessonEvaluate. Also expect references to runtime functions used for output. An unresolved symbol in an intermediate object is normal when a later link supplies it.

## Compile the other source

~~~text
gcc -std=c23 -Wall -Wextra -Wpedantic -I"C:/umicom/installed/umicom-c/include" -c runner.c -o out/runner.o
~~~

Use your own SDK include path on Linux. The -I option adds a directory used when searching for headers. It does not add a compiled library to the link. Conversely, a library search path does not tell the compiler where headers are.

Inspect runner.o with nm. It defines LessonEvaluate and refers to Umicom C functions. This demonstrates a chain of responsibilities rather than two unrelated successful compiles.

## A controlled failure

Try linking only main.o to a new output name. Expect a linker error for LessonEvaluate. This is an intentional exercise, not an instruction to change the production project. Supply runner.o and the libraries in the next lesson to complete the application.

## Review

Explain why copying a header into a project cannot solve every unresolved-symbol error. The declaration tells the compiler how to call a function; the definition must still be present in the final link.

## Read the source

[Open the example source](../../../labs/native/c-build-stages/runner.h).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Inspect generated assembly without guessing its meaning](28-inspect-generated-assembly.md) · [Next: Link a program with an existing native SDK](30-link-with-a-native-sdk.md)
