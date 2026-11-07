<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/05-create-a-validated-account-candidate.md

PURPOSE:
Create a validated account before publishing it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Create a validated account before publishing it

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

## A temporary object is a private draft

The helper add_account creates a local UmiBankingDepositAccount called candidate. The word local means its storage belongs to this function call. The initializer receives the candidate's address so it can fill the record. An address is a location in memory; C uses a pointer to refer to that location.

The initializer first builds its own temporary record, validates it and copies it to the caller only after success. This prevents a partially updated account from becoming visible after a bad currency or balance.

1. Read the UmiStatus returned by umi_banking_deposit_account_init.
2. Follow the call to umi_banking_id_assign for each required identifier.
3. Find the currency validation.
4. Find the check that available_minor must not exceed ledger_minor.
5. Find the final assignment to the output record.

## Ledger, available and reserved

The ledger amount represents the recorded balance in this model. The available amount is the amount recorded as available by the account state. Reserved equals ledger minus available. For 10000 and 8500, the reservation is 1500. These numbers are an observation, not a complete payment policy.

Negative balances are supported when their difference is representable. For example, ledger -100 and available -200 imply a reservation of 100. The implementation also prevents an overflowing subtraction.

## Exercise

Change one account to ledger 100 and available 101. The initializer must refuse it. In the lab, the failed status stops insertion and prints Account refused. Do not “repair” the example by ignoring the status. Restore the valid values and explain which layer rejected the input and why the book was not given an invalid candidate.

A UI can use the same status to show a field-level error while retaining the user's draft for correction.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/finance/banking/deposit_account.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Store money as labelled integer units](04-store-money-as-labelled-integer-units.md) · [Next: Understand ownership and capacity in an account book](06-own-a-bounded-account-book.md)
