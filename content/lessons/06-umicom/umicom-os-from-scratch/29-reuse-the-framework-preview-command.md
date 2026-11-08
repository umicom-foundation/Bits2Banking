<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/29-reuse-the-framework-preview-command.md

PURPOSE:
Reuse the Framework preview command

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Reuse the Framework preview command

## Setup recap

Read Framework docs/learning/cvm-preview.md and install its required current Umicom C SDK first. The OS tools/cvm-preview directory contains a CMake wrapper, not another copy of the compiler or command source. Select a Framework checkout containing cvm_trace.h through UMICOM_OS_FRAMEWORK_SOURCE if its default dependency location is not appropriate.

## Follow composition instead of copying

The wrapper adds Framework examples/cvm_preview as a subdirectory. The Framework example calls the shared presentation service; that service invokes Umicom C. Each layer has one job: the wrapper selects dependencies, Framework owns request state, and Umicom C compiles and executes the small arithmetic language.

The default command prints 42. With --trace it also prints four successful rows. A second quoted argument can supply a complete arithmetic program. The service clears stale presentation state before accepting new work and retains a rejected runtime row without claiming completion.

```powershell
cmake -S tools/cvm-preview -B build/cvm-preview-native -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_PREFIX_PATH=C:/umicom/_local/install/umicom-c -DBUILD_TESTING=ON
cmake --build build/cvm-preview-native --parallel 2
ctest --test-dir build/cvm-preview-native --output-on-failure --no-tests=error
& ".\build\cvm-preview-native\framework-preview\umicom-cvm-preview.exe" --trace "int main(void) { return 7 / 0; }"
```

## Keep a source string in one argument

The deliberate division-by-zero example should print two push rows and a failed divide row, then a diagnostic and exit 1. Its braces and semicolon are source text. Quoting keeps the complete program in one PowerShell argument.

The CMake process fixture also passes source through one explicitly quoted argument. CMake lists use semicolons as separators, so putting an unescaped C program into a generic argument list can split it before the command sees it. The tests compare real command output to make that boundary observable.

## Exercise

Find the source selection, adapter function and executor in their three repositories. Explain why changing only the OS wrapper cannot add a new language operator. Then compare a syntax failure with a runtime failure: syntax produces no rows, while runtime failure can retain completed and rejected rows.

If the wrapper builds against an older Framework dependency, align the selected source and SDK before diagnosing the command. This optional tool is not automatically part of PID-1 startup, a desktop application or a Studio debugger.

## Read the source

[Open the OS source](https://github.com/umicom-foundation/umicom-os/blob/main/tools/cvm-preview/CMakeLists.txt). Use the matching checkout for qualification.

## Continue learning

[Course contents](index.md) · [Previous: Run a fixed runtime trace probe](28-run-a-fixed-runtime-trace-probe.md) · [Next: Distinguish installation from boot integration](30-distinguish-installation-from-boot-integration.md)
