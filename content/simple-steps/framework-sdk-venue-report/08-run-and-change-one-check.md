<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/08-run-and-change-one-check.md

PURPOSE:
Run repeatable consumer tests and make a small change with a predicted outcome.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Run the regression checks and change one input

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A regression check tells you whether a change disturbed a behaviour your team already depends on. The lab uses small checks both for the report functions and for the command-line program.

1. Run all checks and find the entries beginning with `learning.venue.cli.`.

```powershell
ctest --test-dir $build -R '^learning\.venue\.' --output-on-failure --no-tests=error
```

2. Locate `check_limit` in the test source. It accepts 128 rows and refuses a 129th. Notice how both cases use the same kind of row, so count is the one changing variable.
3. In a private practice copy of the accepted CSV, change the visitor count for Main Hall from 48 to 49. Predict the new output for all three totals before running it. Use a different new filename from earlier exercises.
4. Compare your prediction with the report. Run the tests again if you changed the application itself.

**Check your result.** The unmodified project has 13 checks. The practice edit gives 3 rows, 100 minutes and 61 visitors. It changes the source fingerprint.

[Previous — Publish a new receipt](07-publish-a-new-receipt.md) · [Next — Reuse the report](09-reuse-the-report-in-a-client.md)
