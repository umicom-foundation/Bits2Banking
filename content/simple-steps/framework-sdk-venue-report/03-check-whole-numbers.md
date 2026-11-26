<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/03-check-whole-numbers.md

PURPOSE:
Use exact byte spans and venue-specific limits when interpreting CSV fields.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check whole numbers before adding them

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The CSV reader gives the report a text field and its length. The report turns that complete field into a whole number. It checks the result against the venue’s rules before adding it.

1. In `venue_report.c`, find `umi_ascii_uint64_parse`. Trace how the call receives a pointer and length from the CSV row.
2. Check `examples/rejected.csv`. Its final visitor field contains two words where a whole number is required. Pass that file to the application.

```powershell
$rejected = Join-Path $source 'examples\rejected.csv'
Get-Content -LiteralPath $rejected
& "$build\btb-venue-report.exe" $rejected
$LASTEXITCODE
```

3. Look up the venue limits next to `check_row`. A session takes 1 through 1440 minutes and admits up to 10000 visitors. The CSV format alone cannot enforce these choices.
4. Run the parser checks for malformed digits and out-of-range values.

```powershell
ctest --test-dir $build -R '^learning\.venue\.(number|range)$' --output-on-failure --no-tests=error
```

**Check your result.** The application prints a diagnostic beginning with `record 3:` and returns `1`. Both parser checks should pass. Record numbers count the header and each whole CSV record, including a quoted field that spans several text lines.

[Previous — Check the input shape](02-check-the-input-shape.md) · [Next — Preserve the report](04-preserve-the-last-report.md)
