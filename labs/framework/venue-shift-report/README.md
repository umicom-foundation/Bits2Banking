<!--
Bits2Banking
File: labs/framework/venue-shift-report/README.md

PURPOSE:
Help learners build and test the installed SDK venue report.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Venue shift report

![Umicom Foundation](../../../content/assets/branding/umicom-wordmark.svg)

Summarise fictional session records, compare the source fingerprint and optionally write a new receipt. Each row has a room, a duration in minutes and a visitor count. Read the [step-by-step project](../../../content/simple-steps/framework-sdk-venue-report/index.md) for a guided walkthrough.

1. Use a C23 compiler, CMake 3.26 or newer, Ninja and an installed Umicom Framework package with the `base`, `platform` and `output_file` components. Install or select the system dependencies required by that Framework package using the same toolchain.
2. In PowerShell, go to the Bits2Banking checkout. Set `$kit` to your installed SDK and run each command separately. Stop on build errors.

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$kit = 'C:/umicom/installed/framework'
$source = (Resolve-Path '.\labs\framework\venue-shift-report').Path
$build = Join-Path $env:TEMP ('btb-venue-build-' + [guid]::NewGuid().ToString('N'))
Get-Item "$kit/lib/cmake/UmicomFramework/UmicomFrameworkConfig.cmake"
cmake -S $source -B $build -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe "-DCMAKE_PREFIX_PATH=$kit;C:/msys64/ucrt64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON
cmake --build $build --parallel 2
ctest --test-dir $build --output-on-failure --no-tests=error
$sample = Join-Path $source 'examples\shift.csv'
& "$build\btb-venue-report.exe" $sample
```

3. Check for `Rows: 3`, `Minutes: 100` and `Visitors: 60`. Compare the fourth line with `(Get-FileHash -LiteralPath $sample -Algorithm SHA256).Hash`.
4. To save a receipt, choose an unused absolute path in the practice build folder.

```powershell
$receipt = Join-Path $build ('venue-receipt-' + [guid]::NewGuid().ToString('N') + '.txt')
& "$build\btb-venue-report.exe" $sample $receipt
Get-Content -LiteralPath $receipt
```

Use a trusted directory for both input and output. There are no network calls or database connections. The app accepts at most 8192 bytes and 128 data rows. Each session supplies 1 through 1440 minutes and up to 10000 visitors. Room names occupy 1 through 40 UTF-8 bytes. The output contains only totals and the fingerprint.

After a rejected input the program does not create a receipt. If a storage failure occurs during the write, inspect any partial file before retrying with a new path. A matching SHA-256 digest checks byte identity, while the source’s identity depends on a trusted record.
