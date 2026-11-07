<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/10-qualify-and-extend-the-balance-lab.md

PURPOSE:
Qualify and extend the account-balance laboratory

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qualify and extend the account-balance laboratory

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

## Three levels of evidence

Reading source can show how a function is intended to behave. Compiling checks whether the code and dependencies form a valid program for a toolchain. Running checks observes actual behavior. Keep these levels distinct when recording progress.

The lab's CTest case runs the executable and requires a successful exit. The main function independently checks its expected totals and failure preservation, so merely printing a plausible report is insufficient.

1. Configure against an installed SDK that contains the summary API.
2. Build the example.
3. Run CTest with output on failure.
4. Launch the executable directly to read the report.
5. Record the SDK revision, compiler version and result.
6. If a check fails, preserve its output before changing the input or expectation.

Framework's regression target is umicom-banking-deposit-summary-test. Its test names begin framework.banking.deposit.summary. The cases cover empty results, invalid arguments, mixed scope, all account states, full capacity, corrupt counts, invalid unselected rows, duplicate IDs and three overflow paths.

## Extension project

Add a second report for the learner's USD account while retaining the GBP report. Print each on its own labelled line. Predict the USD result as ledger 400, available 300, reserved 100 and one open account. Use the same Framework summary call twice; do not duplicate the aggregation implementation.

Next, add a user-selectable customer field in a learning UI only after defining a synthetic authorization policy. Preserve the original console scenario as a reproducible baseline.

A complete Bank application still needs durable storage, authorization, transaction workflows and UI qualification. This lab supplies a small reusable part and a way to check it; it does not establish readiness for real banking.

## Read the source

[Open the example source](../../../../../labs/framework/account-balances/README.md).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Separate a balance display from spending authority](09-separate-display-from-spending-authority.md)
