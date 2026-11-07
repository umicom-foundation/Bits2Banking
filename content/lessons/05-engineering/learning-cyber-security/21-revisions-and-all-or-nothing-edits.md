<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/21-revisions-and-all-or-nothing-edits.md

PURPOSE:
Keep revision exhaustion from partly changing an identity

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep revision exhaustion from partly changing an identity

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


## Why store a revision?

A revision is a counter that identifies a recorded change. The directory stores one counter for the whole table and another in each row. After adding the example profile, both counters are one. Disabling the profile advances both to two.

A counter has a largest value. `uint64_t` stores an unsigned 64-bit integer; `UINT64_MAX` names its largest value. Adding one at that point wraps an unsigned counter to zero. That arithmetic is defined by C, but it would violate this directory's revision meaning.

## Follow a refused edit

1. Locate the assignment of `UINT64_MAX` to the directory revision. This is a controlled lab injection, not a recommended application edit.
2. The lab copies every byte into `snapshot` using `memcpy`.
3. It asks Framework to re-enable the profile.
4. Framework checks both revision counters before changing either counter or the enabled flag.
5. The returned status is CAPACITY_EXCEEDED. `memcmp` confirms the complete object matches its earlier snapshot.

This is an all-or-nothing edit: either the requested change and both revisions are published, or nothing is changed. The word atomic can describe this failure contract, but it does not imply this structure is a hardware atomic object or safe for concurrent unsynchronised access.

## Read the source in order

Find `umi_security_identity_directory_set_enabled`. First it validates the directory and identifier, then finds the row, then checks counter limits. Only after those decisions does it update the flag and increment the counters. No failing operation remains after publication begins.

Repeated enablement assignments still advance revisions under the existing API contract. A caller should not assume that setting true on an already enabled row is free of effects.

## Exercise

Change the injection to the row revision instead of the directory revision. The requested edit should again fail with the entire directory preserved. Use the supplied regression case named `revision` as a comparison, and record your observed exit status rather than inferring success from compilation alone.

## Check your understanding

Why not increment the directory counter first, then check the row counter? If the second check fails, the directory would claim an edit that did not complete. Validate every precondition before publishing any part of the change.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/security/identity_directory.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Compare a borrowed profile with a saved observation](20-borrowed-profiles-and-observation-copies.md)
