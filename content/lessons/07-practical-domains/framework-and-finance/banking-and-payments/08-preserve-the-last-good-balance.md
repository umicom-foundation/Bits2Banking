<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/08-preserve-the-last-good-balance.md

PURPOSE:
Preserve the last good balance after failure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Preserve the last good balance after failure

A bank application presents records about customers, accounts and money. This module builds one small part: a reliable balance view. A customer identifies whose records are selected; an account holds amounts and a state; a currency identifies the unit of money. All examples use invented records kept in the program's memory. No real bank connection or transfer is made.

## Prepare this laboratory

Install a C23 compiler, CMake 3.26 or later and Ninja. A compiler translates C source into machine instructions. CMake describes the build; Ninja performs the required build steps. Install a matching Umicom Framework SDK containing the finance component. An SDK supplies headers, libraries and package information; its compiler and architecture must match this example.

In PowerShell, run each line separately and stop on errors:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\account-balances"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
& ".\build\btb-account-balances.exe"
~~~

Use your actual SDK path. In Bash, run the same three CMake/CTest commands from the example folder with your native SDK prefix, then run **./build/btb-account-balances**. A package-not-found error points to the SDK installation or prefix. An unknown summary symbol requires a matching updated header and library. The expected report contains two GBP accounts, ledger 12000, available 9500 and reserved 2500 minor units.

## A failure must not publish half a report

Suppose a large book has several valid rows followed by an invalid account. If a screen writes each partial total directly into live state, it may briefly display a misleading result. The summary instead builds a private candidate and publishes it only when every check succeeds.

The lab copies the completed report into previous, then deliberately damages an unrelated synthetic account. The next summary call returns INVALID_STATE. The report's bytes must still match the saved copy.

1. Run the unchanged lab and read its expected totals.
2. Locate the deliberate available_minor = 501 assignment.
3. Compare that record's ledger of 500.
4. Follow the failed summary status.
5. Observe the before/after comparison and success message.

## Integer overflow

A signed 64-bit integer has finite limits. Adding one to INT64_MAX cannot be represented in the same type. Framework's money helper checks the bounds before evaluating the addition and returns CAPACITY_EXCEEDED. It does not wrap the amount into a negative balance.

The regression source covers positive overflow, negative underflow and overflow of the reservation total. Every failure must preserve the caller's previous output. Intermediate sums must fit, even if a later opposite-signed row could reduce the mathematical total.

## Exercise

Read the reserved-overflow case. Its ledger and available totals fit individually, but the sum of reservations does not. Work through both records on paper. Explain why checking only the final ledger total would miss this problem.

Keep the error visible in a UI; retaining a previous view does not make that view fresh. Mark it as the last successful observation while the current request is refused.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/finance_banking/test_deposit_summary.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Project a complete customer balance view](07-project-one-customer-and-currency.md) · [Next: Separate a balance display from spending authority](09-separate-display-from-spending-authority.md)
