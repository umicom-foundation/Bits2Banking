<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/evidence-complete-json-values.md

PURPOSE:
Write complete JSON values into bounded buffers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Write complete JSON values into bounded buffers

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

## A valid prefix is useful

JSON strings need quotes around the value and escapes for quotes, backslashes and control characters inside it. The report writer has a fixed output buffer. If a new value does not fit, it should preserve the prefix already accepted rather than leaving half of an escaped string in the buffer.

## Count before writing

UmiJsonWriterString validates UTF-8, reserves two quote bytes and the terminating NUL, then measures each escaped character against remaining capacity. Only after the complete value fits does it write. Subtraction avoids an expression such as used + requested + 1 overflowing size_t and incorrectly appearing small.

## Exercise

Create a writer with room for an opening bracket but too little room for a quoted value. Append the bracket, then request the string. Check both the returned capacity error and the unchanged bracket. A second append must return the same sticky error until Init resets the writer. The full observation formatter clears failed output instead of presenting the partial document as JSON.

## Reuse the shared owner

Protocol now owns generic JSON emission. Existing language-runtime functions retain their public structure and symbols and delegate to it. Their regression still checks escaping and now also checks atomic refusal and malformed UTF-8. Raw emission accepts trusted JSON syntax; it does not validate that the finished document has a correct object or array structure.

## Verify and recover

~~~powershell
ctest --test-dir build --output-on-failure --no-tests=error
~~~

The lab registers five output contracts. Read actual results; preserve failed or skipped coverage separately. Keep the command, selected inputs and diagnostic when a check fails. Do not run an old binary after a failed build.

[Read the C lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/file-observation/main.c) and [Framework API contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/toolchain/file_observation.h).

[Course contents](index.md) · [Previous lesson](evidence-file-and-total-budgets.md) · [Next lesson](evidence-exclusive-report-files.md)
