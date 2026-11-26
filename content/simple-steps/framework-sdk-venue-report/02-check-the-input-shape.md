<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/02-check-the-input-shape.md

PURPOSE:
Connect an observable report to its CSV header, rows and quoted fields.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read the CSV and predict the totals

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The sample file `examples/shift.csv` lists a room, its session length in minutes and its visitor count. A CSV field can contain a comma when the field is enclosed in double quotes.

1. Open the sample from the previous step and identify its header.
2. Read the first row. `"Gallery, east"` is one field. Its accompanying numbers are `35` and `12`.
3. Add the minutes by hand, then add the visitor counts. Run the application.

```powershell
$sample = Join-Path $source 'examples\shift.csv'
Get-Content -LiteralPath $sample
& "$build\btb-venue-report.exe" $sample
```

4. Open `venue_report.c`. Find `UmiCsvReaderNext`. Successful calls return borrowed fields. They belong to the reader and are usable until another `Next` call or destruction. Notice where the program reads numeric fields before advancing.

**Check your result.** The first three output lines should say `Rows: 3`, `Minutes: 100` and `Visitors: 60`. The fingerprint appears on the fourth line.

[Previous — Select the SDK](01-select-the-sdk.md) · [Next — Check whole numbers](03-check-whole-numbers.md)
