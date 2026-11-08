<!--
Umicom Bits2Banking
File: content/lessons/learning-c/33-review-a-complete-native-consumer.md

PURPOSE:
Review and extend a complete native consumer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review and extend a complete native consumer

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

## Reconstruct the complete contract

The teaching application owns its embedded source string and output value. LessonEvaluate borrows both addresses for the call. It allocates its instruction array on the stack, delegates parsing to umc_compile, then delegates execution to umc_execute. Nothing is retained after the function returns.

Read the function in order:

1. Reject invalid required pointers.
2. Prepare storage for a bounded instruction count.
3. Compile the supplied byte span.
4. Stop immediately if compilation fails.
5. Execute only the published instruction count.
6. Copy the completed result to the caller only on success.

The count is a publication boundary. A compiler may have written partial internal output before rejecting a program; the caller must not execute those bytes just because they exist.

## Extend the tests

Add a case for a negative result, such as return 4 - 9, and expect -5. Add a malformed program and require the old caller value to remain unchanged. Keep these tests in the consumer: they check that this wrapper uses the compiler contract correctly. The compiler repository owns deeper grammar and interpreter tests.

## Add useful diagnostics as a separate design

Before exposing error messages, decide who owns their storage and how long they remain valid. A caller-owned diagnostic structure can avoid hidden allocation, but it needs a documented output rule. Do not return the address of a local array from LessonEvaluate; that array's lifetime ends at return.

## A review checklist

Confirm the header matches the definition, the SDK target is linked, the supported language subset is stated, and errors do not publish stale or partial results. Record build and test results with the actual source revision. A successful arithmetic example is not proof of a complete C compiler or a secure general-purpose sandbox.

## Continue

The Building a Compiler in C course follows tokens, grammar, bytecode and execution in the same Umicom C source. Learning CMake explains target graphs and installed consumers in more detail. Return here whenever a build fails: identify the stage, inspect its inputs, and make the smallest evidence-based correction.

## Read the source

<!-- The lab remains repository source; this earlier checkout-only link is retained for review.
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/runner.c)
-->
[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/c-build-stages/runner.c).

## Continue learning

[Course contents](../../courses/learning-c/index.html) · [Previous: Observe which files an incremental build rebuilds](32-observe-incremental-rebuilds.md)

<details><summary>Publication after success</summary>

The wrapper returns before executing when compilation fails. It passes only the successful instruction count to execution and copies result.value only after execution succeeds. For 4 - 9 the expected value is -5. For malformed source, initialize the caller value to a distinctive value and check both a 0 return and preservation of that value. These are wrapper-contract checks, not proof of a complete C language implementation.

</details>

[Word explanations](../../courses/learning-c/glossary.html) · [Practical guide](../../courses/learning-c/practical-guide.html) · [Learning routes](../../courses/learning-paths.html)
