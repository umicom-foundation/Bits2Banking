<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-bytes-and-version-strings.md

PURPOSE:
Distinguish file bytes from version responses

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Distinguish file bytes from version responses

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

## Start with a question

Suppose a test fails on one computer and succeeds on another. Both compilers print the same version. That observation does not establish that the executable files, runtime libraries or source bytes are identical. Package maintainers can rebuild a release or apply a repair without changing the upstream version string. Decide which file you need to compare before collecting evidence.

## Read the report

The lab calls UmiFileObservationCapture and prints one record per selected path. bytes is the number of bytes read. sha256 is a 64-character hexadecimal digest of those bytes. The three-byte abc fixture has a known digest, so it checks the complete reader-to-report path without requiring a real compiler file. An empty file also has a digest; zero bytes is a valid observation.

## Exercise

Capture abc.bin, then create another file containing abc followed by a newline. Compare their byte counts and digests. Predict the counts before running either command. The second file has four bytes when the newline is one LF byte; a Windows CRLF adds two. Text tools may also add an encoding marker.

## Review the result

A changed digest proves that the observed byte sequences differ, subject to the properties of the digest algorithm. It does not explain which source change caused the difference. Keep the selected filename and the original report beside any diagnostic. Never relabel the digest as a test result or a digital signature.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](language-support-regression-and-source-map.md) · [Next lesson](evidence-selection-before-reading.md)
