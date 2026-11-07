<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/07-project-one-customer-and-currency.md

PURPOSE:
Project a complete customer balance view

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Project a complete customer balance view

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

## One reusable projection

A projection is a view computed from source records. UmiBankingDepositAccountBookSummarise produces one without changing the book. Bank, Trader account views and other clients can call a shared contract rather than each writing their own loop.

The output contains the selected customer and currency, account count, counts for pending/open/blocked/closed states, and ledger/available/reserved totals. All matching statuses contribute to the totals. The status counts let a view explain why some accounts need separate attention.

1. Find the temporary UmiBankingDepositSummary called candidate.
2. Observe validation of the requested customer and currency.
3. Follow the count check before the loop.
4. Follow record and duplicate-ID checks, including unselected records.
5. Find the customer and currency comparison that selects a row.
6. Follow checked additions into private temporary values.
7. Find the final output assignment.

The call rejects a corrupted book even if the damaged row would not be selected. Otherwise a filter could hide damage and make the same book appear valid in one view and invalid in another.

## Empty is a valid result

A valid customer-and-currency request with no matching accounts succeeds with zero counts and totals. That differs from a failed call. A screen should show “No matching accounts” for the first case and a clear load or validation error for the second.

## Exercise

Ask for customer unknown with GBP and inspect the result. Then corrupt the source count beyond capacity. The first call should succeed with an empty summary; the second should fail without changing its output. Explain why both cases should not be rendered as an ordinary zero balance.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/finance/banking/deposit_account_book.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Understand ownership and capacity in an account book](06-own-a-bounded-account-book.md) · [Next: Preserve the last good balance after failure](08-preserve-the-last-good-balance.md)
