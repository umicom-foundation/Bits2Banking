<!--
Umicom Bits2Banking
File: content/lessons/learning-c/28-inspect-generated-assembly.md

PURPOSE:
Inspect generated assembly without guessing its meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect generated assembly without guessing its meaning

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

## From C operations to processor instructions

Assembly is a readable notation for instructions and related data used by a processor toolchain. Different processors have different instruction sets. Even on one processor, compiler options can change the emitted instructions while preserving defined C behaviour.

Generate a listing:

~~~text
gcc -std=c23 -S -O0 -g main.c -o out/main.s
~~~

Open the file as text. Search for main and LessonEvaluate. You should find code associated with main and a reference to the external function. Exact labels, prefixes, instruction spelling and calling conventions depend on the target. Do not compare the file byte for byte with a screenshot from another machine.

## Read in layers

1. Find the text representing the embedded arithmetic program.
2. Find the code section containing main.
3. Locate the call or reference to LessonEvaluate.
4. Find a branch associated with handling failure, if it remains visible in this compiler output.
5. Record the compiler target and options beside your observations.

A calling convention defines how arguments, return values and preserved registers cross a function boundary. The C compiler implements that convention. Writing a correct assembly function requires following the same contract, not merely returning the expected number once.

## Compare optimisation

~~~text
gcc -std=c23 -S -O2 main.c -o out/main-optimised.s
~~~

Compare the two listings. Optimisation may remove temporary storage, combine operations or change control flow. A shorter listing is not automatically a faster application; actual work and measurement matter. Debugging optimised code can also show variables differently because their source-level storage may no longer exist.

## Connect to Umicom Kernel

Kernel startup assembly establishes a machine state before C code can rely on a stack and other conventions. That is a different responsibility from this hosted program's main function, where the operating-system runtime already performed startup. Follow the RISC-V course when you are ready to inspect the Kernel entry path.

## Exercise

Draw the call boundary between main and LessonEvaluate. Label input pointers, byte length, output pointer and success result. You do not need to understand every generated instruction to identify that contract.

## Read the source

[Open the example source](../../../labs/native/c-build-stages/main.c).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Inspect the source after preprocessing](27-inspect-preprocessed-source.md) · [Next: Understand object files and unresolved symbols](29-object-files-and-symbols.md)
