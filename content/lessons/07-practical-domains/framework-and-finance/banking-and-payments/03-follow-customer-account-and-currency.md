<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/03-follow-customer-account-and-currency.md

PURPOSE:
Follow customer, account and currency identities

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Follow customer, account and currency identities

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

## Read the model before adding a screen

The example has four accounts. Two belong to the customer named learner and use GBP. One belongs to learner and uses USD. One belongs to another customer and uses GBP. Each account has its own identifier. The account identifier answers “which account?” and the customer identifier answers “whose account?”; neither field is a display name or password.

1. Open main.c in any text editor.
2. Find the four calls to add_account.
3. Write a table with columns account ID, customer ID, currency, ledger and available.
4. Circle only the rows whose customer is learner and currency is GBP.
5. Add those two ledger amounts by hand: 10000 + 2000 = 12000.

~~~text
Four account records
        |
        v
Validate each record
        |
        v
Select customer learner AND currency GBP
        |
        v
Two matching accounts -> one GBP summary
~~~

The word “AND” matters: matching either field would include unrelated money. Framework represents identifiers with UmiFinancialId and currency with UmiCurrency. The record initializer applies their validators before storing the account.

## Exercise and explanation

Change the other customer's GBP ledger and available amounts from 500 to 700. Predict the learner's report before running it: the selected totals stay unchanged. This demonstrates scope through data rather than through a screen label. In a real application, the server or trusted service must authorize the selected customer; accepting a customer ID from a form alone is not authorization.

The account book does not create customer profiles or prove that an ID belongs to the current user. Those relationships require the appropriate identity and banking services. Keep that responsibility visible when connecting a UI.

## Read the source

[Open the example source](../../../../../labs/framework/account-balances/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Next: Store money as labelled integer units](04-store-money-as-labelled-integer-units.md)
