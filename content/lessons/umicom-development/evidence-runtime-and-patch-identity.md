<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-runtime-and-patch-identity.md

PURPOSE:
Separate selected libraries from loaded runtime identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate selected libraries from loaded runtime identity

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

## A pathname is not a loaded module

Several copies of a runtime library can exist on one computer. Hashing a file you selected tells you about that file, while an application may load another copy through its search path. The file-observation report therefore keeps loadedModuleIdentity false. Do not edit this field to true because the filename looks familiar.

## Connect a diagnostic to the right evidence

Record the runtime version printed by the failing process, its source/build identity where known, and the package or loaded-module path supplied by an appropriate platform diagnostic. Then hash the relevant on-disk file for comparison. Establishing an upstream patch requires trustworthy package/source information, not just a version number or an unfamiliar digest.

## Exercise

Write two statements about the same report. First: “I observed these bytes at this explicit DLL path.” Second: “The failing process loaded this DLL and contains the vendor repair.” List the additional evidence required for the second statement. The report supports the first statement but cannot supply the missing process and patch information.

## Keep regressions honest

Leave the original failing test enabled while investigating a runtime dependency. Added diagnostics and authored regression cases do not repair the loaded package. After obtaining an appropriate runtime through your normal installation process, rebuild where required and execute the targeted cases. Preserve skips and failures separately from passes and retain the package identity with the result.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-before-after-comparison.md) · [Next lesson](restart-own-the-right-operation.md)
