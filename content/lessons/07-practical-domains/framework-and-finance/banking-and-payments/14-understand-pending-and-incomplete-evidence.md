<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/14-understand-pending-and-incomplete-evidence.md

PURPOSE:
Understand pending and incomplete evidence

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand pending and incomplete evidence

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

## Booked and pending describe different evidence

A booked transaction has been recorded in the provider's account history. A pending transaction is still an observation that may change. In this exercise, a pending purchase is -999.00. That intentionally large value makes an incorrect inclusion easy to notice: if it entered the booked equation, the expected closing balance would be very different.

UmiBankStatementReview reports pendingRows separately. It also reports mutable booked rows, missing transaction identifiers and page hints. These fields help a reader judge the limitations of the imported evidence. A client should not hide them just because balancesMatch is true.

## A matching total has a narrow meaning

Imagine two missing booked rows: a 20.00 credit and a 20.00 debit. Their net movement is zero. Removing both would leave the same closing calculation while making the statement incomplete. Likewise, an invented statement could contain amounts that add correctly. Arithmetic alone cannot establish provenance or authenticity.

The final line of the program makes that distinction explicit. The result is a comparison of the imported observations with supplied assumptions. It is not a bank confirmation, settlement confirmation or fraud decision.

## Practice reading the result

1. Run the original example. Expect two booked rows, one pending row and one selected-scope row outside the period.
2. Find the checks of balancesMatch and difference.
3. Explain why the pending debit is still worth displaying to a user even though it is excluded from the booked equation.
4. Write a review note stating the account, currency, period and number of rows used.
5. Add a separate line identifying what evidence would establish completeness, such as the full provider statement and its page boundaries.

## Application design connection

A Bank screen can show the expected closing balance, supplied closing balance and difference together. Pending entries should have a visible state. Missing IDs and page hints should remain available in the review details. The screen should call the same Framework review service as this lab so its display and exported review use one calculation.

A local simulation is useful for testing these controls. It must remain visibly identified as simulation. Do not turn a synthetic row into a real account observation merely by changing its label.

## Check your understanding

Can a nonzero difference still be a valid review result? Yes. It means the evidence and assumptions do not currently reconcile. The next lesson follows that discrepancy without disguising it as an importer failure.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Previous: Select an account, currency and period](13-select-account-currency-and-period.md) · [Next: Investigate a statement difference](15-investigate-a-statement-difference.md)
