<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-file-and-total-budgets.md

PURPOSE:
Bound one file and the complete request

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Bound one file and the complete request

## Prepare your tools

Install a C23 compiler, CMake 3.25 or later, Ninja and a matching Umicom Framework SDK containing the toolchain file-observation service. A terminal runs written commands; CMake prepares build instructions and Ninja performs compilation. Stop on a configure or build error before launching any existing executable. These examples use Windows UCRT64 and an SDK at C:\umicom\installed\framework; substitute your own paths. The lab reads ordinary files and needs no GUI, server or credentials.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\native\file-observation"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
[IO.File]::WriteAllBytes("$PWD\build\abc.bin", [byte[]](97,98,99))
.\build\file-observation.exe "$PWD\build\abc.bin"
~~~

Expect a JSON record with three bytes and the SHA-256 digest of abc. This is file evidence, not a passing build or runtime result. A missing SDK header or symbol requires a matching SDK installation.

## Memory needs an explicit budget

The native reader allocates space for one selected file, hashes it, then frees that buffer before reading the next file. This limits peak file-buffer memory. A per-file limit alone does not limit the total work of reading many files, so Framework also limits combined bytes and the number of selected paths.

## Use subtraction to find remaining work

The service starts with a 256-MiB combined budget. Before each read it subtracts bytes already observed and takes the smaller of that remainder and the caller-selected per-file limit. If the budget is exactly exhausted, the reader may still accept an empty file but must refuse a nonempty one. The example lab chooses one MiB per file; the CLI defaults to 64 MiB.

## Exercise

Use the native CLI with --max-bytes 2 on the three-byte abc fixture. It should refuse the request. Increase the limit to 3 and capture again. A decimal byte count such as 3 is accepted; negative values, fractional numbers and values above the service maximum are refused.

## Test without enormous fixtures

The admission regression replaces only the read and digest boundaries. It checks that a fifth 64-MiB read receives a zero-byte allowance after four successful reads. This tests the orchestration without allocating 256 MiB. The real-file suite separately checks actual small files and platform errors. Keep both forms of coverage; one cannot establish the other.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-observation-ownership.md) · [Next lesson](evidence-complete-json-values.md)
