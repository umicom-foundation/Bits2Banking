<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/18-qualify-the-statement-client.md

PURPOSE:
Qualify the statement client

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qualify the statement client

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

## What this check covers

A regression check repeats a known workflow so a later change can be compared with an explicit expected result. This lab checks exact totals, selected scope, pending exclusion, owned archive lifetimes, a reopened calculation, a valid discrepancy, an empty known period, an unknown scope and a failed later CSV row.

It uses REQUIRE rather than the C assert macro. REQUIRE is ordinary control flow, so its checks remain present when an optimized build defines NDEBUG. A failed expression prints its source line, goes to the shared cleanup section and returns exit code one. Exit code zero indicates that the program reached the expected end.

## Run a deliberate qualification sequence

1. Configure the laboratory against the installed SDK you intend to use.
2. Build it and read any compiler diagnostics.
3. Run the executable directly to see its explanatory output.
4. Run CTest. CTest is the test runner registered by CMake; it starts the same executable and reports its exit status.
5. Record the source revision, SDK revision, compiler version and command output with the result.
6. Repeat after a relevant source or SDK change.

A successful build alone does not establish that the checks ran. A successful terminal example also does not prove that a Bank button dispatches the same service or displays its result correctly.

## Extend to an interface test

For a Bank review screen, use the same fictional observations. Open the import dialog, select the file, choose account and currency, enter the dates and balances, and calculate. Verify visible totals and the pending count. Change closing balance and verify that the previous match is invalidated. Save to a user-selected location, close, reopen and compare the assumptions. Attempt an invalid replacement and check that a clear error appears while the prior review remains available.

These are observable acceptance criteria. Record screenshots only from synthetic data. Never mark them passed because the source contains a callback or because another component's tests passed.

## Troubleshooting

If the package cannot be found, inspect the configured SDK prefix. If symbols are missing at link time, compare the installed headers and libraries with the same Framework revision and confirm bank_feed is exported. If a REQUIRE fails, read that expression and the relevant contract before changing the expectation.

Do not weaken an expected amount just to obtain a pass. First decide whether the business rule, the implementation or the test fixture is wrong. Keep the reason beside the corrected regression so future contributors can understand the boundary.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Refuse a partial statement import](17-refuse-a-partial-statement-import.md)
