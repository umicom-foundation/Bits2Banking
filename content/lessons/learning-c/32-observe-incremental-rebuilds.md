<!--
Umicom Bits2Banking
File: content/lessons/learning-c/32-observe-incremental-rebuilds.md

PURPOSE:
Observe which files an incremental build rebuilds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Observe which files an incremental build rebuilds

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

## The dependency graph

A build system records which outputs depend on which inputs. In this lab, main.c and runner.c compile separately. The executable depends on both compiled results and the linked SDK. A correct incremental build rebuilds outputs whose recorded inputs or commands have changed.

Configure once using the README. Then build with command output visible:

~~~text
cmake --build build --verbose
~~~

Repeat the command without editing anything. An up-to-date build should have no compilation work. If it recompiles, inspect the displayed command and dependency timestamps before deleting the build directory.

## Make controlled observations

1. Edit LESSON_FACTOR in main.c and save. Rebuild. main.c should need compilation and the executable should need relinking.
2. Restore the factor and rebuild.
3. Add an explanatory comment to runner.h. A normal timestamp-based build can rebuild both including C files even when runtime behaviour is unchanged.
4. Record the actual steps rather than assuming a comment-aware cache exists.

Header dependencies matter because declarations can affect many translation units. Compiler options, generated inputs and toolchain changes can matter even if .c bytes are unchanged. Reusing an object safely requires all relevant inputs to match the build's validity rules.

## Connect build selection and test selection

Building fewer objects does not automatically identify every affected test. Tests may depend on data, configuration, generated resources or several modules. Start with explicit target dependencies and test ownership. A failed-test list is useful evidence, but passing an old test does not prove it remains valid after shared code changes.

The Umicom project build services record plans and qualification information for this reason. A new compiler is not required to obtain ordinary incremental compilation: the existing CMake/Ninja graph already provides it when dependencies are correct.

## Exercise

Create a small table with change, expected compilation, expected link and observed result. Include a main.c edit, a runner.h edit and no edit. Explain any difference before modifying the build configuration.

## Read the source

[Open the example source](../../../labs/native/c-build-stages/CMakeLists.txt).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Read diagnostics at the stage that produced them](31-read-diagnostics-by-stage.md) · [Next: Review and extend a complete native consumer](33-review-a-complete-native-consumer.md)
