# Statement reconciliation API example

A statement comparison asks a small, precise question: does the opening balance,
plus booked credits, minus booked debits, equal the closing balance?

This optional Framework integration example assumes that you can read C code and
build a CMake project. It demonstrates the statement review API using invented
data and Umicom Framework's shared implementation. It is reference material for
contributors integrating financial applications, separate from the numbered
programming course.
It does not connect to a bank, transmit a payment or validate the authenticity of
a statement.

## Follow the numbers

Start with **100.00 GBP**. A booked receipt adds **12.50 GBP** and a booked
payment removes **2.25 GBP**. The expected closing balance is **110.25 GBP**.
A pending payment of **999.00 GBP** is not booked, so it does not enter that sum.

If the reported closing balance is **110.26 GBP**, the difference is **0.01 GBP**:
reported closing minus expected closing. A zero difference is useful evidence,
but missing or duplicated source records could still happen to cancel out.

## Build the native example

First build and install the current Umicom Applications SDK to
`C:\umicom\installed\applications`. The library and headers must come from the
same build. The owner chooses this visible installation folder.

1. Open PowerShell and configure the example against that installation:

   ```powershell
   Set-Location "C:\umicom\Umicom-Bits2Banking"
   $env:Path = "C:\msys64\ucrt64\bin;$env:Path"
   cmake -S ".\labs\native\statement-reconciliation" -B ".\build\statement-reconciliation" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications
   ```

2. Build and run its regression checks:

   ```powershell
   cmake --build ".\build\statement-reconciliation" --parallel 2
   ctest --test-dir ".\build\statement-reconciliation" --output-on-failure --no-tests=error
   ```

3. Run the two comparisons:

   ```powershell
   & ".\build\statement-reconciliation\statement-reconciliation.exe"
   & ".\build\statement-reconciliation\statement-reconciliation.exe" 110.26
   ```

The first comparison should print `Difference: 0.00`; the second should print
`Difference: 0.01`. Both exclude one pending entry.

If CMake cannot find `UmicomFramework`, check the installation prefix and confirm
that `lib\cmake\UmicomFramework\UmicomFrameworkConfig.cmake` exists beneath it.
A missing `bank_feed` component means the installed SDK predates this feature.
Do not copy individual headers over an older library.

## Trace the shared implementation

Open `labs/native/statement-reconciliation/main.c` in the repository. The program:

1. Parses a closing balance with an explicit decimal scale.
2. Imports a bounded, invented transaction response.
3. Selects one account, one currency and an inclusive period.
4. Reviews the balances through `UmiBankStatementReview`.
5. Releases the feed and prints the copied result.

The contracts live in Framework's `include/umicom/bank_feed/statement.h`.
The same code serves Trader, Bank and TMS. Education examples consume that
contract instead of maintaining a separate banking algorithm.

## Explore the boundaries

Change the booked payment to a pending payment and explain the new total.
Move a transaction outside the selected period. Add a transaction in another
currency and confirm that it is not added to the GBP balance. Try an invalid
date and a coefficient too large for the decimal representation.

Booking dates use the provider's written calendar date. A timezone offset does
not move the entry into another reporting day in this review. Previous or next
page flags, missing identifiers and mutable booked entries remain visible
limitations. Those observations do not establish regulatory or accounting approval.
