<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/06-own-a-bounded-account-book.md

PURPOSE:
Understand ownership and capacity in an account book

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand ownership and capacity in an account book

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

## A bounded collection

The account book contains an array and a count. An array is a sequence of fixed-size slots. The count records how many slots contain active records. This book has at most UMI_BANKING_MAX_ITEMS accounts, currently 64. A count is not permission to access arbitrary memory: it must remain within the array's capacity.

The lab initializes the whole book with zeroes. umi_banking_deposit_account_book_add checks the account, checks capacity, checks for an existing ID, and copies the record into the next slot.

1. Locate the items array and count member in the public structure.
2. Follow the add function's error returns before the write.
3. Find the expression that increments count after insertion.
4. Explain why the local candidate can go out of scope after the copy.
5. Explain why a pointer returned by the find function still belongs to the book.

## Borrowed storage

A borrowed pointer gives temporary access to someone else's object. It must not be freed independently. It must not outlive the book or be used while another thread is changing it. Copy data deliberately if it must be retained beyond that owner's lifetime.

The new summary call accepts a const book pointer. Const documents that this operation observes the book rather than editing it. The caller must still serialize access: const does not create a lock.

## Exercise

Call add_account twice with the same account identifier in a non-full book. The second insertion should fail with ALREADY_EXISTS. The count remains unchanged. Then read the regression case called capacity to see how all 64 slots are exercised.

Avoid storing arbitrary network record counts directly into the structure. Validate imported records through a bounded admission path before making them live.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/finance/banking/deposit_account_book.h).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Create a validated account before publishing it](05-create-a-validated-account-candidate.md) · [Next: Project a complete customer balance view](07-project-one-customer-and-currency.md)
