<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/04-preserve-the-last-report.md

PURPOSE:
Show how local totals and an assignment at the end protect caller-owned output.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve the accepted report after a refused row

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Suppose a caller already holds a report from an earlier shift. The current file starts well and has a bad field near the end. A total from only the first few rows would give the caller the wrong handover.

1. In `BtbVenueSummarise`, find the temporary `next` record and the final `*report = next` assignment.
2. Trace the last row of `examples/rejected.csv`. Before the error, the temporary record contains one accepted row. The call returns an error before the final assignment.
3. Read `check_refused` in `test_venue_report.c`. The test fills the caller’s record with an earlier result before passing the bad input.
4. Run the tests for refused data and capacity.

```powershell
ctest --test-dir $build -R '^learning\.venue\.(number|malformed|limit)$' --output-on-failure --no-tests=error
```

**Check your result.** All three tests should pass. The prior values are still 7 rows, 80 minutes and 41 visitors in the refusal cases. `bad_record` can report the location independently of the accepted totals.

[Previous — Check whole numbers](03-check-whole-numbers.md) · [Next — Check a fingerprint](05-check-the-source-fingerprint.md)
