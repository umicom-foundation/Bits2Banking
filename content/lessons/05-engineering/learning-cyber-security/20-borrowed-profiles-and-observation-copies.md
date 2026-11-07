<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/20-borrowed-profiles-and-observation-copies.md

PURPOSE:
Compare a borrowed profile with a saved observation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Compare a borrowed profile with a saved observation

This lesson starts with a small C program using synthetic identity metadata. It explains the terms needed for the exercise before following the corresponding Framework operation.

## Set up this lab

A terminal is an application where you type commands. A compiler translates C source into machine instructions; CMake prepares the build rules; Ninja carries out those rules. This lab also needs an installed Umicom Framework SDK containing its security library. You can read the lesson without installing anything.

1. Open the Bits2Banking checkout and find `labs/framework/governed-identities`. Read `main.c` and `CMakeLists.txt`.
2. In PowerShell on Windows, use your UCRT64 C23 compiler with CMake 3.26 or newer and Ninja. Set the SDK path below to your actual installation; it must match the compiler and architecture.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\governed-identities"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure
& ".\build\btb-governed-identities.exe"
```
3. In Bash, change into the same lab and supply your SDK location.

```bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/your/framework-sdk
cmake --build build
ctest --test-dir build --output-on-failure
./build/btb-governed-identities
```
Stop at a failed command. A missing `UmicomFrameworkConfig.cmake` means CMake cannot locate the installed SDK. A link error means the SDK may not match the headers or compiler; do not replace Framework calls with local copies. Successful execution ends with `Governed identity lab passed.` The lab uses synthetic metadata and does not create operating-system users or login sessions.


## Two ways to read the same record

A pointer holds an address. A borrowed pointer lets a function's caller inspect storage owned elsewhere. It does not transfer ownership. A copied structure stores another value in different storage.

The lab asks Framework for `borrowed`, then copies `*borrowed` into `observed`. The star operator reads the object at an address. At this moment both observations show an enabled identity, but they have different lifetimes and different behaviour after an edit.

## Trace the edit

1. Locate `const UmiSecurityIdentityProfile *borrowed`. Here `const` prevents this pointer from being used to modify the profile directly. It does not prevent the directory owner from modifying the same storage.
2. Locate `const UmiSecurityIdentityProfile observed = *borrowed`. This captures the earlier field values.
3. Follow `umi_security_identity_directory_set_enabled` with `false`. Framework changes its stored row.
4. Read the next check: `borrowed->enabled` is now false, while `observed.enabled` remains true. The arrow follows a pointer; the dot accesses a structure value.
5. At `finish`, `free(directory)` releases the row storage. No later statement may dereference `borrowed`. Such a pointer would be dangling: it still holds an address but no longer names a live owned object.

## Apply this to application commands

A Bank transfer or Studio extension command should check current identity state when the operation is authorised. A saved enabled flag can become stale. It is useful for comparing observations, not as permanent permission to perform future work.

The directory does not synchronise threads. One thread reading while another writes can cause a data race. Put both access paths behind the application's existing service or lock. Copying a value without coordinating concurrent access is not a substitute for that rule.

## Exercise

Draw two boxes labelled directory row and observation copy. Draw `borrowed` as an arrow to the first box. Cross out the directory box at `free`, then mark which values remain readable. The observation copy lives until its own scope ends, but it remains an old observation.

## Check your understanding

Does `const` keep the observed identity enabled forever? No. It restricts access through one expression. Ownership, lifetime, synchronisation and current authorisation each require their own checks.

## Read the source

[Open the example source](../../../../labs/framework/governed-identities/main.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Validate a public identity table before using its rows](19-validate-a-public-identity-table.md) · [Next: Keep revision exhaustion from partly changing an identity](21-revisions-and-all-or-nothing-edits.md)
