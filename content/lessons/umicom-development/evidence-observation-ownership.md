<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-observation-ownership.md

PURPOSE:
Own an observation independently of its inputs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Own an observation independently of its inputs

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

## Borrow during a call, own after it

The caller owns its array of input paths. Capture reads those strings during the call, then stores its own copies. The returned observation owns paths and digests until UmiFileObservationDestroy. This allows a command parser or file chooser to release its temporary argument storage without invalidating the report.

## Follow one successful request

Initialise UmiFileObservation *observation to NULL. Pass its address to Capture. On success, UmiFileObservationAt returns a borrowed pointer into the observation. Read that item while the observation remains alive. Do not free the item or its path. Destroy the owner once, after formatting or saving has finished.

## Exercise

Copy the path into a writable character buffer before capture. After capture succeeds, modify that buffer and inspect the stored item. The captured path should retain its original bytes. Now modify the selected file and format the existing observation again. It should still describe the earlier read because formatting performs no filesystem I/O.

## Recover safely

Failure returns no partial observation and leaves the output owner unchanged. The output pointer must be NULL initially; this prevents silently replacing a live allocation. Release an earlier observation explicitly before capturing another one. In a GUI, keep the object alive until the worker or serializer has finished, and never share mutable input strings with a concurrent writer.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-selection-before-reading.md) · [Next lesson](evidence-file-and-total-budgets.md)
