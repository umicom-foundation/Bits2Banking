<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/banking-and-payments/11-read-a-statement-as-observations.md

PURPOSE:
Read a statement as observations

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a statement as observations

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

## Start with one row

A bank statement lists observations about money moving into or out of an account. A CSV file stores a table as text: commas separate fields and a line ending normally ends a record. A record can also contain quoted text, so a banking program must use a CSV parser rather than split every line at each comma.

The example has nine columns: account, transaction, reference, information, booking_date, currency, amount, status and mutability. The header identifies their order. The account identifies the scope; transaction identifies one observation within that account. Information is a description for a person to read. The booking date is the provider's written date. GBP labels the currency and 12.50 is the amount. BOOK means booked. Immutable means the observation is reported as unchanging. These values describe imported evidence, not permission to make a payment.

## Follow import ownership

1. Locate observations near the top of main.c. Adjacent string literals form one array of characters.
2. Locate UmiBankFeedCsvCreate. The first argument points to those characters. The second gives their length without the terminating zero byte.
3. The third argument is &feed: the address of the pointer variable that will receive the created object. The final argument receives the location of an import problem.
4. Check the returned status before calling any function that reads feed.

UmiBankFeed is opaque. That means the client uses a handle and public functions instead of changing the object's private fields. Framework owns validation and storage. The client owns the handle's lifetime and must eventually pass it to UmiBankFeedDestroy.

## Why the import is a separate step

Imported rows can be incomplete, duplicated or malformed. Recording them immediately as ledger entries would confuse observations with approved accounting instructions. This laboratory calculates a comparison only. An application needs a separate reviewed posting workflow before observations can become ledger entries.

## Exercise and expected result

Read the six rows and group them by account and currency on paper. Four belong to lesson-account in GBP, one belongs to another-account in GBP and one belongs to lesson-account in EUR. Do not add all six amounts together. In the next lessons, the review selects an account, a currency and a date range before calculating money movements.

If import fails, record the status and the issue coordinates. Correct the input or the selected import mapping. Do not silently discard the failed row and describe the remaining prefix as a complete statement.

## Read the source

[Open the example source](../../../../../labs/framework/statement-review/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/banking-and-payments/index.html) · [Next: Calculate statement money exactly](12-calculate-statement-money-exactly.md)
