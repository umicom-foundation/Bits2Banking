<!--
Umicom Bits2Banking
File: content/lessons/learning-c/26-read-the-build-map.md

PURPOSE:
Read the map from source to executable

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read the map from source to executable

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

## What the program does

Open main.c in your editor. The function main is where this hosted C program starts. It prepares text describing a second, very small program: int main(void) { return 6 * 7; }. LessonEvaluate compiles and runs that text through Umicom C. The outer program then prints Value: 42.

There are two different execution layers. GCC builds the outer application for your processor and operating system. At runtime, Umicom C parses the inner text into a bounded instruction array and interprets it. The inner source is data until that explicit call.

~~~text
main.c + runner.c
       | GCC and linker
       v
native application
       | starts and calls LessonEvaluate
       v
embedded source -> Umicom C instructions -> integer result
~~~

## Follow the files

1. Read runner.h. A declaration tells another source file the function's name, parameter types and return type.
2. Read runner.c. The definition contains the instructions that implement that function.
3. Find #include "runner.h" in both C files. A shared declaration helps the compiler check their agreement.
4. Find target_link_libraries in CMakeLists.txt. This connects the consumer to the existing compiler library.
5. Build and run the lab using its README. Record the command, exit status and printed value separately.

A header is not the compiled function body. Including runner.h lets main.c be compiled, but the linker still needs the object produced from runner.c. That object needs the Umicom C libraries in turn.

## Investigate a change

Change only LESSON_FACTOR from 6 to 5 in a private copy of main.c. Predict Value: 35, then rebuild and run. If the result remains 42, check that you rebuilt the same directory and launched that output. Do not assume every executable with the same name contains the latest code.

## Check your understanding

Explain which program GCC compiles and which text Umicom C compiles. Then identify the file that owns printing and the file that owns the compiler calls. Keeping those responsibilities separate is the same principle used by thin applications that call Framework services.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/README.md)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/README.md).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Next: Inspect the source after preprocessing](27-inspect-preprocessed-source.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](25-check-file-digests-independently.md)

<details><summary>The two execution layers</summary>

GCC compiles main.c and runner.c into the outer native application. At runtime, that application passes the arithmetic source string to Umicom C. main.c owns printing; runner.c owns the compile-and-execute calls. Changing LESSON_FACTOR requires rebuilding the outer application because that macro contributes bytes to its embedded string.

</details>

[Word explanations](../../courses/learning-c/glossary.html) · [Practical guide](../../courses/learning-c/practical-guide.html) · [Learning routes](../../courses/learning-paths.html)
