<!--
Umicom Bits2Banking
File: labs/native/compiler-experiments/README.md

PURPOSE:
Guide a first compiler experiment using the existing Umicom C implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect a small compiled program

This lab calls Umicom C. It contains an instruction viewer and three groups of checks, not another lexer or interpreter. It supports the arithmetic language described in the Umicom C checkout used for the build.

## Prepare the environment

You need Bits2Banking and Umicom C checkouts, CMake 3.24 or newer, Ninja and a compiler supporting C23. Follow [development setup](../../../content/lessons/06-umicom/24-development-setup.md) if these tools are unfamiliar. A terminal is a window in which you type commands. Run one command at a time and stop if it reports an error.

## Windows PowerShell

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\compiler-experiments" -B ".\build\compiler-experiments" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_C_SOURCE_DIR=C:/umicom/umicom-c -DBUILD_TESTING=ON
cmake --build ".\build\compiler-experiments" --parallel 2
& ".\build\compiler-experiments\btb-compiler-inspect.exe" 'int main(void) { return 2 + 3 * 4; }'
ctest --test-dir ".\build\compiler-experiments" --output-on-failure --no-tests=error
```

## Linux Bash

Replace both checkout locations before running these commands.

```sh
cd /path/to/Umicom-Bits2Banking
cmake -S ./labs/native/compiler-experiments -B ./build/compiler-experiments -G Ninja -DCMAKE_C_COMPILER=cc -DUMICOM_C_SOURCE_DIR=/path/to/umicom-c -DBUILD_TESTING=ON
cmake --build ./build/compiler-experiments --parallel 2
./build/compiler-experiments/btb-compiler-inspect 'int main(void) { return 2 + 3 * 4; }'
ctest --test-dir ./build/compiler-experiments --output-on-failure --no-tests=error
```

The expected instruction order is push 2, push 3, push 4, multiply, add, return. The expected result is 14 with six instructions executed. The source offsets identify byte positions in the supplied string. The checks cover grammar, arithmetic and instruction validation; three passing test groups are expected, not yet claimed.

## Read each stage

1. Configuration locates existing compiler sources and creates a build plan.
2. Building compiles those sources and the lab consumers.
3. The quoted argument keeps the entire source program together.
4. The viewer prints instructions only after compilation succeeds.
5. Execution receives a fuel allowance equal to the instruction count.
6. CTest runs the three check executables; it does not build missing files.

Change the expression to `(2 + 3) * 4` and predict 20. Change it to `8 / (2 - 2)`: compilation should succeed but execution should refuse division by zero. The earlier instruction listing is not a successful result.

## Investigate a failure

A missing checkout is a configuration problem. A missing function at link time means an implementation was not linked. A compile diagnostic from the viewer concerns the small input language, not the host C compiler. Keep these three meanings separate.

Use [experiment sheets](EXPERIMENTS.md) to predict results. Store your command, source revision and actual outcome together. These examples perform no operating-system calls from interpreted bytecode and do not qualify a full C compiler, a sandbox for arbitrary native code or any hardware target.

