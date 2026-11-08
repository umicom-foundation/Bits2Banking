<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-exclusive-report-files.md

PURPOSE:
Preserve earlier evidence when saving a report

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve earlier evidence when saving a report

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

## A report is a historical observation

Overwriting yesterday’s report removes the comparison point that made it useful. UmiFileObservationSave formats the captured object before opening its destination, then requests exclusive file creation. An existing path is a refusal, even when the new bytes would be identical. The parent directory must already exist.

## Use the native command

Choose a private evidence folder and a new filename. Run umicom observe-files --file ABSOLUTE_PATH --report NEW_ABSOLUTE_FILE with actual absolute paths in place of the placeholders. Read the exit status and the saved JSON. Do not infer successful saving solely from the presence of a file: a failed write can leave partial bytes.

## Exercise

Save a report, record its contents, then repeat the command with the same destination. Expect refusal and unchanged earlier contents. Next select the input file itself as the report destination. The command must refuse replacement and the selected input must remain unchanged. The storage regression checks both cases.

## Handle incomplete output

After a write or flush error the service retains a partial file for diagnosis. Preserve it, correct the storage problem and choose a different destination. Do not turn a persistence error into a success because hashing completed earlier. Capture status and persistence status describe different operations. Keep private paths out of public examples and review evidence before sharing it.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-complete-json-values.md) · [Next lesson](evidence-before-after-comparison.md)
