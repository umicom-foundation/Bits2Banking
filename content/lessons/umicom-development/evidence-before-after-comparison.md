<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-before-after-comparison.md

PURPOSE:
Compare selected bytes before and after a run

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare selected bytes before and after a run

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

## Define the selection first

A before-and-after comparison is meaningful only when you know which inputs were selected. Include the same explicit source and tool paths in both captures. A missing or added file is a selection difference, not merely a changed digest. The command does not recursively discover dependencies or read every file used by a compiler.

## Perform the sequence deliberately

Capture before.json under a new absolute filename. Keep the selected inputs stable. Execute the separate build or tests and preserve their actual output. Capture after.json under another filename. Parse both JSON reports and compare path, bytes and sha256 together. Keep the original reports even if you also create a summary.

## Exercise

Capture abc.bin, change its contents to abd and capture again. The byte count remains three while the digest changes. Revert to abc and capture a third time. The first and third digests match, demonstrating why two matching observations cannot exclude an intervening edit.

## State only what the evidence shows

The reports are sequential reads, not an atomic snapshot of a workspace. They do not bind the digest to a particular build process or prove that an executable was rebuilt. Pair them with source revisions, configuration, build output and test results. If any identity is unknown, record it explicitly instead of filling it from the current checkout.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-exclusive-report-files.md) · [Next lesson](evidence-runtime-and-patch-identity.md)
