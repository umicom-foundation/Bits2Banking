<!--
Umicom Bits2Banking
File: content/lessons/learning-c/27-inspect-preprocessed-source.md

PURPOSE:
Inspect the source after preprocessing

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect the source after preprocessing

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

## What preprocessing means

Before C declarations and expressions are compiled, directives beginning with # are processed. Our example includes a header, chooses a default macro value and turns that value into text. A macro is a token replacement rule; it is not a variable stored while the program runs.

## Produce an intermediate file

1. Create out as described above.
2. Run the following command.
3. Open out/main.i in your editor and search for const char source.

~~~text
gcc -std=c23 -E main.c -o out/main.i
~~~

The .i file contains expanded includes and preprocessing results. It can be much larger than main.c because standard library declarations are included. Line markers help tools relate the expanded text to original source locations.

The two macros LESSON_STRING and LESSON_STRING_INNER deliberately form two steps. The outer step expands LESSON_FACTOR; the inner # operator converts the resulting token to a string literal. Adjacent string literals are combined by C, so the embedded source contains the chosen number.

## Try a configuration change

~~~text
gcc -std=c23 -DLESSON_FACTOR=5 -E main.c -o out/main-five.i
~~~

Compare the line containing source in the two intermediate files. The source file has not been edited, but the compiler input has changed because a command-line definition changed. A build identity therefore needs relevant options as well as file content.

## Do not confuse a comment with configuration

An ordinary explanatory comment does not supply executable C tokens. However, source location, debug information and preprocessing constructs can make simplistic text-based reuse rules unsafe. A build tool must use an explicit dependency and configuration model, not assume that every apparently cosmetic edit is irrelevant.

The official [GCC preprocessing reference](https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html) documents these options. For this exercise the important observation is the actual expanded line you see, not the length of the generated file.

## Exercise

Write down the default factor, the overridden factor and the expected runtime result for each. Keep intermediate files in out rather than replacing main.c. The source remains the file you maintain.

## Read the source

[Open the example source](../../../labs/native/c-build-stages/main.c).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Read the map from source to executable](26-read-the-build-map.md) · [Next: Inspect generated assembly without guessing its meaning](28-inspect-generated-assembly.md)
