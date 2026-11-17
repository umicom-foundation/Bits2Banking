<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/01-prepare-a-shared-boundary.md

PURPOSE:
Teach prepare one shared c boundary.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prepare one shared C boundary

[Course contents](index.md) · [Next](02-follow-the-c-contract.md)

## What you will learn
A language is a way to write instructions. A compiler translates a source file into machine instructions. An object file contains compiled instructions and names that still need to be connected. A linker joins object files and libraries into an executable program. An archive is a container of object files, not a program you can launch.

An application binary interface, abbreviated ABI, is the agreement between compiled functions: argument sizes, registers, stack layout, exported names and return values. Different source languages can cooperate when they deliberately use the same ABI. This does not mean that arbitrary source syntax can be pasted into another language.

## Before you type commands
1. If files, folders or terminals are unfamiliar, begin with [Computing from the beginning](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/computing-from-the-beginning/index.html), then [Learning C](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/learning-c/index.html). Return when you can create a file and recognise a function call.
2. Open the Bits2Banking checkout in a terminal. Keep practice output in its build folder. Never use a system directory for exercises.
3. Check cmake --version and gcc --version. This series needs CMake, Ninja and a C23 compiler. A missing command means the tool is absent or its directory is not on PATH; it does not mean your program is wrong.
4. Obtain an installed Umicom Framework SDK for the same operating system and processor as your compiler. Its prefix is the directory containing lib/cmake/UmicomFramework. A source checkout alone is not an installed SDK.
5. Read the existing activity-adapters README. Do not download a model, run a full application build or install every language to start this lab.

## Build the common archive
Run these PowerShell commands separately from the Bits2Banking repository. Replace the SDK prefix if your installation differs. Stop at the first error.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/activity-adapters -B build/activity-adapters -G Ninja -DCMAKE_C_COMPILER=gcc "-DCMAKE_PREFIX_PATH=C:/umicom/installed/framework"
cmake --build build/activity-adapters --parallel 2
ctest --test-dir build/activity-adapters --output-on-failure --no-tests=error
~~~

Expected artifacts include libbtb-activity-adapters.a with a GNU toolchain and two registered C checks. A successful configure is not a successful build. Missing UmicomFrameworkConfig.cmake means the SDK prefix needs correction. Do not copy arbitrary headers to silence it.

~~~text
C / C++ / Rust / Zig / Fortran / D / Odin / Nim caller
                         |
                  BtbActivityNext(int)
                         |
          existing C activity model + Framework status
~~~

## Try it and explain it
Predict the result of BtbActivityNext(41) and BtbActivityNext(1000). The answers are 42 and -1. The limit is checked in one C implementation; each foreign-language client must preserve the rejection result. Record the compiler version, target and exact command with every experiment. No timing ranking can be inferred from this tiny demonstration.

## Read the complete source

[labs/native/activity-adapters/bridge.h](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/bridge.h)
