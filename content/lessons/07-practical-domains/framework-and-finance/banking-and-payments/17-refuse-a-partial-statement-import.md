<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/17-refuse-a-partial-statement-import.md

PURPOSE:
Refuse a partial statement import

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Refuse a partial statement import

Learn how a banking client turns imported observations into a review that can be explained, checked and reopened. Follow one small program that calls the shared Framework services.

This laboratory is a small C program. A compiler translates its source into an executable; CMake describes the build and Ninja runs the required build steps. Use an installed Umicom Framework SDK containing the bank_feed component, a C23 compiler, CMake and Ninja from the same toolchain. On Windows, open PowerShell and use the UCRT64 tools. An SDK is a set of headers and libraries used by another program; these commands consume it rather than rebuild Framework.

1. Open PowerShell.
2. Enter the commands below, using your installed SDK directory if it differs.
3. Read the configure result before building. If CMake cannot find UmicomFrameworkConfig.cmake or the bank_feed component, install the matching SDK first; do not replace the library with a local imitation.
4. Run the executable, then the registered laboratory check. A failing check prints its source line and exits with a nonzero status.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\statement-review"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/applications" -DBUILD_TESTING=ON
cmake --build build --parallel 2
& ".\build\btb-statement-review.exe"
ctest --test-dir build --output-on-failure --no-tests=error
```
On Linux, use the same source and an SDK built for Linux. In Bash, run cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=/your/sdk/path -DBUILD_TESTING=ON, then cmake --build build, ./build/btb-statement-review and ctest --test-dir build --output-on-failure --no-tests=error. Replace /your/sdk/path with the actual installation directory. Windows libraries cannot be linked into a Linux executable.

Open main.c in a text editor to follow the calls. The program uses fictional observations held in memory; it does not connect to a bank or change any account. The [Learning C course](../../../../courses/learning-c/index.html) explains declarations and control flow in more depth.

## A later bad row must not become a quiet omission

A parser may read several valid records before reaching an invalid one. Returning the earlier records as though the whole statement succeeded would hide missing evidence. The Framework CSV import contract refuses the complete import and clears its output handle when a record is invalid.

The lab copies its character array into damaged. sizeof(observations) gives the full array size, including its final zero. memcpy copies exactly that many bytes into an array of the same size. The original observations stay unchanged.

strstr finds the text PDNG in this known teaching fixture. It returns a pointer to the match or NULL when absent. The code checks the pointer before writing. It then replaces those four bytes with FAIL, a deliberately unsupported status value. This use of strstr is a fixture mutation, not a CSV parser for production input.

## Read the failure checks

1. Import damaged with the same explicit byte length as the original.
2. Require a status other than UMI_STATUS_OK.
3. Require rejected to remain NULL.
4. Continue using the separate, valid copy retained earlier.

The failed import must not destroy or mutate another object the caller already owns. This separation allows an application to keep a currently reviewed statement while reporting why a newly selected file could not be imported.

## Output preservation and user experience

A failure message should identify the failed operation and, when available, the logical record and column. Quoted CSV records can span physical lines, so a record number is not always a text editor line number. Some whole-input checks, such as invalid UTF-8 or forbidden control bytes, happen before row parsing and may have no specific record coordinate.

Do not print confidential row contents into a general diagnostic log. A useful log can record the status, coordinates, import size and a user-approved evidence identity without copying account descriptions or balances.

## Exercise

Change the malformed status back to PDNG in your exercise copy. Import should then succeed, so the deliberate-failure check should fail. This confirms that the check actually distinguishes its intended bad input from valid data.

For an application regression, also retain a known valid review, attempt a malformed replacement, and verify that the user can still inspect the original review. Clearing the entire screen on any import error would discard useful working context.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Own and reopen a review](16-own-and-reopen-a-review.md) · [Next: Qualify the statement client](18-qualify-the-statement-client.md)
