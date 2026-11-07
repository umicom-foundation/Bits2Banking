<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/13-select-account-currency-and-period.md

PURPOSE:
Select an account, currency and period

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Select an account, currency and period

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

## Define the question before calculating

A review request asks a precise question: for this account, in this currency, between these dates, do the observations explain the change from the supplied opening balance to the supplied closing balance? UmiBankStatementRequest stores that question. Its account and currency strings are borrowed during the call. Keep them alive until the call returns.

The laboratory selects lesson-account, GBP and 2026-10-12 for both firstDate and lastDate. The range includes both dates. UmiBankStatementDate accepts a real Gregorian calendar date in YYYY-MM-DD form. A malformed date or an impossible day is refused. This function does not read a computer clock or guess the user's locale.

## Trace each excluded row

1. The credit and debit on 12 October belong to the selected account and currency, so they affect the comparison.
2. The pending row on the same day is counted but does not change booked movement.
3. The 50.00 receipt on 11 October belongs to the scope but falls outside the period, so outsidePeriodRows becomes one.
4. The 900.00 row belongs to another account and is excluded.
5. The 80.00 EUR row uses another currency and is excluded.

Opening balance means the balance immediately before the first date. Closing balance means the balance after the last date. A starting value from the middle of the selected day would make the equation misleading even if every transaction was parsed correctly.

## Empty and unknown are different

Later in main.c, the request changes to 13 October. The imported account is known, but there are no rows in that period. Zero movement is a valid result. The supplied opening and closing balances are both 100.00, so their arithmetic matches.

Next, the account changes to unknown-account. Framework returns UMI_STATUS_NOT_FOUND because the import contains no observations establishing that account and currency scope. It leaves the result unchanged. The caller must use the status to distinguish this failure from a valid zero-movement period.

## Exercise

Draw a table with one line per imported observation and columns for account match, currency match, date match and booked status. Mark each condition before predicting the totals. This is the same reasoning a user interface should communicate through clear selection controls and visible scope labels.

For feeds containing timestamps with offsets, this review uses the provider's written calendar date. Do not relabel the result as a UTC-day statement without an explicit conversion policy and matching tests.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Calculate statement money exactly](12-calculate-statement-money-exactly.md) · [Next: Understand pending and incomplete evidence](14-understand-pending-and-incomplete-evidence.md)
