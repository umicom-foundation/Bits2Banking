<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/19-validate-a-public-identity-table.md

PURPOSE:
Validate a public identity table before using its rows

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Validate a public identity table before using its rows

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


## What is a public table?

A table stores several records. A record groups related values, such as a person's stable identifier and display name. A public C structure exposes those fields to its caller. That is convenient for inspection, but the caller can accidentally set an impossible row count.

Framework's directory contains a fixed array and a count of used entries. The count is a claim about the array, not proof that the entries exist. An index is a position in the array; reading an index outside its bounds is undefined behaviour, meaning C gives no reliable result.

## Follow the example

1. Find the first `calloc` call. It allocates the entire directory and fills its storage with zeros. The lab checks for failure before writing any fields.
2. Find `umi_security_identity_directory_add`. It validates a profile before copying it into a row. The identifier and display name must contain a terminating zero byte within their arrays.
3. Find the line assigning `SIZE_MAX` to `directory->count`. This deliberately damages a disposable teaching object. It does not enlarge the array.
4. The next lookup must return NULL. The enablement call must return INVALID_ARGUMENT. Framework checks the count before entering its row loop.
5. The comparison with `snapshot` shows that rejection did not repair or partly change the directory. The caller still owns the damaged object and its recovery decision.

## Why inspect every used row?

Imagine the first row has the requested identifier, but the second row contains a name with no terminating zero. Returning immediately at the first match would conceal damaged table state. The directory validates all used rows before the lookup. This establishes one consistent boundary for all callers.

## Exercise

In a separate copy of the lab, change the injected count to one more than `UMI_SECURITY_GOVERNANCE_MAX_IDENTITIES`. Predict the result, then build and run. It should still be rejected. Restore the original example afterwards. Never try this experiment on application data.

## Check your understanding

Does an array grow when its count grows? No. Storage capacity and the count field are separate. A correct count must stay within the allocated capacity; each used row must also satisfy its own text and type rules.

## Read the source

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/governed-identities/main.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Next: Compare a borrowed profile with a saved observation](20-borrowed-profiles-and-observation-copies.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Previous lesson](18-review-security-evidence.md)
