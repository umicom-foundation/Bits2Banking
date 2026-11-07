# Account balance laboratory

This C23 program creates four synthetic accounts in memory and asks Umicom Framework for one customer's GBP summary. No bank, broker, network, password, payment or persistent store is used. A blocked account is included in the displayed totals, but the report does not authorize spending.

## Prepare

Install a C23 compiler, CMake 3.26 or later and Ninja. Obtain a matching installed Umicom Framework SDK with the finance component and the new deposit-summary API. The SDK is a directory containing headers, compiled libraries and CMake package files. Use the same compiler and architecture as the SDK.

On Windows, open PowerShell. These commands assume MSYS2 UCRT64 tools and the SDK at the stated locations. Change the SDK path if it is installed elsewhere.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\account-balances"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
& ".\build\btb-account-balances.exe"
~~~

On Linux or macOS, open a terminal in this example folder. Set the prefix to the matching native SDK.

~~~bash
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom-sdk" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
./build/btb-account-balances
~~~

Run each command separately and stop after an error. A missing package means the prefix does not lead to the installed package. An unknown summary function usually means that the source header or installed library is older than this example. Reinstall a matching SDK rather than copying a header over an older library.

## Expected result

~~~text
learner GBP: 2 accounts, 1 blocked
Ledger minor units: 12000
Available minor units: 9500
Reserved minor units: 2500
Invalid source refused; previous summary preserved.
This balance view grants no payment or account access.
~~~

A minor unit is the smallest accounting unit chosen for a currency. For GBP in this example, 100 units mean one pound. The code prints integer units explicitly rather than assuming every currency has two decimal places.

## Follow the calls

1. **umi_banking_deposit_account_init** validates an account in a temporary object. Each identifier, currency, status and balance relationship must be valid.
2. **umi_banking_deposit_account_book_add** copies a valid account into the bounded book. The caller still owns the book.
3. **UmiBankingDepositAccountBookSummarise** selects one customer and currency, validates the whole book and totals with Framework's checked money arithmetic.
4. The deliberate malformed record demonstrates refusal without partial publication. **memcmp** compares bytes only for this same-object before/after check; it is not a general financial equality operation.

Read [the banking course](../../../content/courses/framework-and-finance/banking-and-payments/index.html). Try changing the USD balance: the GBP summary should remain the same. Then change the selected currency and explain each expected total before running the program. Authorization, storage, bank connectivity and transfers require separate services.
