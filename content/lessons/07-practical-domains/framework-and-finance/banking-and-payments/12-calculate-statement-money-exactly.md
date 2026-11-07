<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/12-calculate-statement-money-exactly.md

PURPOSE:
Calculate statement money exactly

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Calculate statement money exactly

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

## A labelled integer represents an amount

A decimal amount can be represented by an integer coefficient and a scale. A scale of two means two digits appear after the decimal point. The coefficient 10000 at scale two represents 100.00. UmiDecimal stores these values together. The currency is kept separately because an amount without its currency is not a complete financial value.

The laboratory calls UmiDecimalParse with the text 100.00, its six-character length, the requested scale 2 and the address of openingBalance. Parse means convert text into a structured value. Check UMI_STATUS_OK before using the result. The function refuses excess fractional precision rather than rounding it without a policy.

## Work through the equation

The selected day contains a booked credit of 12.50 and a booked debit of 2.25. Starting from 100.00 gives:

```text
100.00 + 12.50 - 2.25 = 110.25 GBP
```
The imported debit is written as -2.25. The review exposes debits as a positive total that is subtracted in the equation. Reversing its sign again in a client calculation would produce an incorrect answer. Framework performs the calculation once; the client displays its result.

## Inspect the verification helper

money_is parses an expected amount and calls UmiDecimalCompare. The comparison returns a status and writes -1, 0 or 1 to order. Zero means the values are equal, even if their valid scales differ. Checking only the coefficient would confuse 125 at scale one with 125 at scale two.

1. Run the program and locate the equation line.
2. Read the requirements that check credits, debits, netMovement, expectedClosing and difference.
3. In an exercise copy, change the booked credit to 12.51 and predict the new expected closing value.
4. Rebuild. The old expected result should now fail. Update the intended closing assumption and exercise expectation together, explaining the one-penny change.

## Limits are part of the contract

Fixed-size integers have a maximum and minimum. Checked decimal operations report a capacity failure if a required exact intermediate value cannot be represented. A banking client must surface that failure instead of using an old result or treating it as zero. Floating-point conversion is not a repair for an out-of-range exact calculation.

A scale of two is an explicit teaching choice here. Applications must obtain the required precision from their currency and product rules rather than assuming every currency or instrument uses two decimal places.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Read a statement as observations](11-read-a-statement-as-observations.md) · [Next: Select an account, currency and period](13-select-account-currency-and-period.md)
