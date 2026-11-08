<!--
Umicom Bits2Banking
File: content/lessons/learning-c/31-read-diagnostics-by-stage.md

PURPOSE:
Read diagnostics at the stage that produced them

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read diagnostics at the stage that produced them

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

## An error message is evidence

A diagnostic describes a problem observed by a particular tool. First identify that tool and the stage it was performing. The same word error can describe a missing include, an invalid C expression, an unresolved symbol or a failed runtime check.

Use a private working copy for deliberate mistakes. Keep the original example available so you can compare one change at a time.

| Observation | First place to inspect |
|---|---|
| runner.h not found | Source location and include search paths |
| A C syntax diagnostic | The reported source and preceding statement |
| LessonEvaluate unresolved | Objects and libraries in the link |
| Embedded source could not be evaluated | The string passed to Umicom C |
| Boundary test returns nonzero | The specific condition in test_runner.c |

## Follow a runtime rejection

The test passes the text return 6 / 0 inside the supported tiny program. Compiling the outer C file is still valid: the embedded program is a string. Umicom C accepts the grammar and rejects the arithmetic during interpretation. LessonEvaluate reports failure and leaves the caller's old value unchanged.

The test also supplies a syntax error and null arguments. These are different causes with the same public success/failure result. A production interface may expose richer diagnostics; this small wrapper deliberately teaches the output contract first.

## Keep a useful record

Record the exact command, source revision, compiler version, first meaningful diagnostic and exit status. If you use Tee-Object to save output in PowerShell, inspect the native command's exit code immediately. Printing a log is not evidence of success.

Do not remove a warning flag merely to make a transcript look clean. Determine whether the warning identifies a real ownership, range or portability issue. The [GCC warning reference](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html) explains individual options.

## Exercise

Predict which stage rejects each of these changes: remove a semicolon in main.c; omit runner.o from the link; change the embedded text to divide by zero. Explain why only the last case can reach the already-built application's execution path.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/test_runner.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/test_runner.c).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Link a program with an existing native SDK](30-link-with-a-native-sdk.md) · [Next: Observe which files an incremental build rebuilds](32-observe-incremental-rebuilds.md)

<details><summary>Three different failures</summary>

A missing C semicolon is a compile-stage failure. Omitting runner.o leaves LessonEvaluate unresolved at link time. Division by zero inside the embedded source reaches the built application and is rejected by the Umicom C execution step. The wrapper returns 0 and leaves the old caller value untouched.

</details>

[Word explanations](../../courses/learning-c/glossary.html) · [Practical guide](../../courses/learning-c/practical-guide.html) · [Learning routes](../../courses/learning-paths.html)
