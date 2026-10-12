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

### Install the shared SDK first

An SDK contains the headers, compiled libraries and CMake package files that
another project needs. Building Applications creates those files in its build
tree; installing copies the supported set into the folder chosen below.
Adding a folder to `CMAKE_PREFIX_PATH` does not install anything.

Run these steps from a current Applications checkout whose Framework submodule
contains the statement API. Use the same UCRT64 toolchain for both projects.
Each guard stops the sequence if the preceding command fails.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --preset windows-ucrt64-all-debug -DBUILD_TESTING=ON -DUMICOM_BUILD_NATIVE_TOOL=ON
if ($LASTEXITCODE -ne 0) { throw "Applications configuration failed; stop here." }
cmake --build --preset windows-ucrt64-all-debug --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Applications build failed; do not install an incomplete build." }
cmake --install ".\build\windows-ucrt64-all-debug" --prefix "C:\umicom\installed\applications"
if ($LASTEXITCODE -ne 0) { throw "SDK installation failed; stop here." }
if (-not (Test-Path -LiteralPath "C:\umicom\installed\applications\lib\cmake\UmicomFramework\UmicomFrameworkConfig.cmake")) {
    throw "The installed Framework package is missing from the selected prefix."
}
```

Use the full installation command shown here. A component-only installation is
insufficient because the package configuration and export files are also needed.
The file check confirms that the package entry point was installed; successful
example configuration and linking still need to confirm its dependencies.

### Configure and run the example

1. Open PowerShell and configure the example against that installation:

   ```powershell
   Set-Location "C:\umicom\Umicom-Bits2Banking"
   $env:Path = "C:\msys64\ucrt64\bin;$env:Path"
   cmake -S ".\labs\native\statement-reconciliation" -B ".\build\statement-reconciliation" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications
   if ($LASTEXITCODE -ne 0) { throw "Example configuration failed; do not build or test yet." }
   ```

2. Build and run its regression checks:

   ```powershell
   cmake --build ".\build\statement-reconciliation" --parallel 2
   if ($LASTEXITCODE -ne 0) { throw "Example build failed; do not run tests yet." }
   ctest --test-dir ".\build\statement-reconciliation" --output-on-failure --no-tests=error
   if ($LASTEXITCODE -ne 0) { throw "Example tests failed; review their output before continuing." }
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
<!-- The earlier diagnosis is retained for review. It assumed an older SDK;
the explanation below also covers incomplete installations and disabled features.
A missing `bank_feed` component means the installed SDK predates this feature.
-->
A missing `bank_feed` component can mean an older SDK or an incomplete
installation. Check that the Framework build exports the component, then install
the complete matching build.
Do not copy individual headers over an older library.

If you chose another installation folder, change `CMAKE_PREFIX_PATH` to that
folder. For a custom library directory, you can instead pass
`-DUmicomFramework_DIR=C:/your-install/lib64/cmake/UmicomFramework`, using the
directory that actually contains the **installed** package configuration.
Do not point it at the generated configuration file inside the Framework build
tree: that file alone does not supply the installed target definitions.

After a configuration failure, fix its first error and rerun configuration in
the same example build directory. Do not continue to Ninja or CTest yet:
`build.ninja` is created only after successful generation, and tests are
registered by configuration. This example registers three checks:
`education.statement.match`, `education.statement.difference` and
`education.statement.invalid`. A run with no tests is not successful
qualification.

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
