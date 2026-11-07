<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/15-investigate-a-statement-difference.md

PURPOSE:
Investigate a statement difference

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Investigate a statement difference

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

## Successful calculation can report disagreement

A function status answers whether an operation completed according to its contract. A business result answers the question asked by that operation. Those are separate ideas. UmiBankStatementReview can return UMI_STATUS_OK while result.balancesMatch is false.

The laboratory changes the supplied closing balance from 110.25 to 111.25 without changing the imported rows. Expected closing stays 110.25. Difference is supplied closing minus expected closing, so it becomes +1.00. A negative difference would mean the supplied closing balance is below the calculated value.

## Follow the investigation in order

1. Confirm the selected account and currency. A correct amount from another account cannot reconcile this statement.
2. Confirm the first and last dates and the meaning of the opening balance.
3. Compare the original observation count with the imported count. Inspect failed imports and page hints.
4. Separate pending observations from booked movement.
5. Review duplicate and missing identifiers without silently removing entries.
6. Compare individual amounts and dates with the original source.
7. Record the remaining difference and the evidence needed to resolve it.

These steps are an investigation method, not an automatic instruction to adjust a ledger. A balancing entry requires its own explanation and authorized accounting workflow.

## Inspect the code

After setting closingBalance, main calls the same review function again. It checks both the success status and the expected nonzero difference. This guards against an interface that mistakes a mismatch for a broken calculation or displays a stale green match from the previous request.

An application should invalidate an old result when the account, dates, balances or source observations change. A fresh review must correspond to the values currently shown on screen. Disabling a button is not sufficient if an old result still looks current.

## Exercise

In a separate copy, use 109.25 as the supplied closing balance and predict the sign of difference. Keep a written equation before changing the expectation. Restore the original example afterwards so its registered check remains reproducible.

## When the function fails

For an invalid date range, missing account scope or arithmetic overflow, the status reports failure and output remains unchanged. Do not treat that preserved output as a new result. Display the failure beside the current inputs and retain the prior reviewed result only with a clear identity and timestamp if your application supports review history.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Understand pending and incomplete evidence](14-understand-pending-and-incomplete-evidence.md) · [Next: Own and reopen a review](16-own-and-reopen-a-review.md)
