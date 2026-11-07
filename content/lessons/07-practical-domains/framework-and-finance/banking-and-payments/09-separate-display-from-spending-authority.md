<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/09-separate-display-from-spending-authority.md

PURPOSE:
Separate a balance display from spending authority

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Separate a balance display from spending authority

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

## A view is not a payment decision

The lab includes a blocked account in its totals. This is intentional: the report describes recorded balances across the selected scope. It does not say that all displayed money may be transferred. A payment service must consider identity, account state, approvals, reservations, limits and the exact instruction being submitted.

For a UI, separate three questions:

1. What records were successfully observed?
2. May the current user view these records?
3. May the current user request this specific operation now?

The summary answers only part of the first question. Passing a different customer ID does not grant access. Neither a disabled button nor a hidden tab is an authorization boundary; the service receiving an operation must enforce its policy too.

## Map the view to widgets

A balance header can show currency and ledger total. A nearby label can show the number of blocked accounts. An error message can explain why the latest refresh failed. A transfer button should obtain its availability from the payment workflow, not from the arithmetic expression available_minor > 0.

The same contract can feed a desktop label, a web response or a mobile view model. The frontend is responsible for formatting and interaction; the shared engine remains responsible for the validated projection.

## Exercise

Write a small table with columns record state, displayed balance, and permitted operation. Include an open account and a blocked account with equal numeric balances. Explain why the balance alone is insufficient to fill in the final column.

Do not connect this learning example to real credentials or live payments. Extend it first with synthetic authorization decisions and explicit regression cases.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/finance/banking/deposit_account_book.h).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Preserve the last good balance after failure](08-preserve-the-last-good-balance.md) · [Next: Qualify and extend the account-balance laboratory](10-qualify-and-extend-the-balance-lab.md)
