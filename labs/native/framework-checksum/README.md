# Check file contents with Umicom Framework

A checksum is a compact value calculated from bytes. This command reads one file
and prints its SHA-256 checksum. It uses Framework's existing implementation.
It never opens the input file for writing.

## Files and ownership

- `checksum.h` describes a borrowed stream and a caller-owned result buffer.
- `checksum.c` reads chunks; Framework owns all digest arithmetic.
- `main.c` owns the open/close lifetime and reports errors.
- `test_checksum.c` checks known answers and chunk boundaries.

The program reads from the stream's current position. A read error can leave
that position advanced while the result buffer remains unchanged. This teaching
adapter does not provide a filesystem snapshot: close editors and avoid changing
the input during comparison. Paths use the C runtime's narrow-character support;
a production Windows file picker should use Framework's Unicode path services.

## PowerShell

Install the C23 compiler, CMake and Ninja described in Learning C. Obtain an
installed Framework SDK containing the base component. Replace the prefix below
with its actual location. Run each command separately and stop on an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/framework-checksum -B build/learning/checksum -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build/learning/checksum --parallel 2
ctest --test-dir build/learning/checksum --output-on-failure --no-tests=error
& ".\build\learning\checksum\btb-checksum.exe" ".\README.md"
(Get-FileHash ".\README.md" -Algorithm SHA256).Hash.ToLowerInvariant()
~~~

Both final lines should show the same 64 hexadecimal characters when the file
has not changed. Their letter case is not part of the digest.

## Bash

Use a C23-capable C compiler, CMake, Ninja and an installed native Framework SDK.

~~~bash
cmake -S labs/native/framework-checksum -B build/learning/checksum -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DBUILD_TESTING=ON
cmake --build build/learning/checksum --parallel 2
ctest --test-dir build/learning/checksum --output-on-failure --no-tests=error
./build/learning/checksum/btb-checksum README.md
sha256sum README.md
~~~

On a system without sha256sum, use its documented SHA-256 utility. Compare only
the digest, because the second command can also print the filename.

## Try a failure

Run the command with no argument. It should print usage and fail. Give the path
of a file that does not exist: it should print an open error and no digest.
The exact operating-system error wording varies. Tests create temporary files;
a refusal to create these is a failed environment requirement, not a passing test.

If CMake cannot find UmicomFramework, check the installation prefix and whether
it contains the base component. A missing symbol at link time can mean the header
and library come from different SDK revisions. Do not copy the SHA implementation
into the example to work around a missing package.

## What a match means

Matching digests help compare content. They do not identify who supplied a file.
For downloads, a trusted publisher must authenticate the expected digest through
an appropriate signed release or another trusted channel. This exercise does not
implement signatures, password storage or file encryption.

