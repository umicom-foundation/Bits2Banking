<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/go-statement-tools.md

PURPOSE:
Provide practical first steps and a result to check for Go Statement Tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Go Statement Tools

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Save the supplied program as `statement.go`. Type `go run statement.go` and count the accepted records. [Read and validate CSV rows](../../lessons/04-web/go-statement-tools/01-read-and-validate-csv-rows.md)
2. Add `postedTotals` and the updated `main` from the next lesson. Run the program again. [Print deterministic posted totals](../../lessons/04-web/go-statement-tools/02-print-deterministic-posted-totals.md)
3. Find the pending reserve movement in the sample CSV and circle the amount. Check it was excluded from the printed reserve total. [Print deterministic posted totals](../../lessons/04-web/go-statement-tools/02-print-deterministic-posted-totals.md)

**Check your result.** The parser accepts six movements. The report prints clearing 0, operating 900 and reserve 1750 in that order.

[Continue in the full course](../../courses/go-statement-tools/index.html) · [All course guides](index.md)
