<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/04-store-money-as-labelled-integer-units.md

PURPOSE:
Store money as labelled integer units

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Store money as labelled integer units

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

## Understand the unit

An integer is a whole-number value. The lab stores GBP amounts in pennies, so 10000 means £100.00. The number has meaning only with its currency and unit convention. A bare 10000 printed without a label could be pounds, pennies, dollars or an unrelated count.

Framework's UmiMoney combines an integer amount, a decimal scale and a currency. The deposit records used here already store minor-unit counts. The summary adds these counts through umi_money_add; it does not perform currency conversion or choose a visual decimal format.

1. Locate ledger_minor and available_minor in the account record.
2. Note the int64_t type: a signed integer with exactly 64 bits.
3. Locate the GBP currency passed to the summary.
4. Read the output labels: each explicitly says minor units.
5. Explain why the USD account cannot be added directly to the GBP total.

## Do not invent a conversion

Adding 100 GBP and 100 USD into a number labelled GBP loses information. Conversion requires a rate, rate direction, date, rounding policy and evidence of the rate source. This lab deliberately keeps separate summaries; it supplies none of those conversion services.

The rule “divide everything by 100” is also too broad for a general application. A display must obtain the applicable currency and scale convention instead of guessing from a number's size.

## Exercise

Change the selected currency object to USD. The existing main function's expected-value checks will then need deliberate updates. Predict ledger 400, available 300, reserved 100 and one account. Do not alter only the label: change the selection and its expected results together. A failing check after the change is useful evidence that the scenario's old expectation no longer matches its input.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/finance/money.h).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Follow customer, account and currency identities](03-follow-customer-account-and-currency.md) · [Next: Create a validated account before publishing it](05-create-a-validated-account-candidate.md)
