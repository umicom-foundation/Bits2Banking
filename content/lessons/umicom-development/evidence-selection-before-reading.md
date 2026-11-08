<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-selection-before-reading.md

PURPOSE:
Validate a complete file selection before reading

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Validate a complete file selection before reading

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

## Separate syntax from storage

A path can be syntactically valid while naming a missing file. The Framework service first validates every path and the selection limits. Only then does it open the first file. This lets a caller reject a relative path at the end of the list without first reading unrelated earlier inputs. All paths must be absolute, ordinary UTF-8 paths.

## Trace the admission loop

Open file_observation.c and locate the loop before allocation. UmiOutputFileValidatePath checks the shared path syntax without creating a file. UmiUtf8Validate checks encoding. Exact duplicate strings are refused. Different spellings that reach the same file are not merged; the service makes no filesystem-identity claim about aliases.

## Exercise

Pass the absolute abc fixture followed by a relative path. The request should fail without a partial JSON report. Then pass a valid absolute path to a missing file. That selection passes syntax admission but fails during reading. Compare these two failures and identify which phase produced each.

## Explain the boundary

The library returns an index when a particular selected path fails. General argument errors use SIZE_MAX, meaning no selected index applies. Do not add one to this sentinel and display it as a filename number. The CLI checks the sentinel before presenting a one-based number. GUI callers should preserve this distinction when highlighting an invalid selection.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-bytes-and-version-strings.md) · [Next lesson](evidence-observation-ownership.md)
