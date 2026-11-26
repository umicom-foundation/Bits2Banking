<!--
Umicom Bits2Banking
File: content/simple-steps/extension/bootstrap-native-statements.md

PURPOSE:
Give learners an additional practical case for Bootstrap and Native Statement Reports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Export a posted correction with both writers

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The C statement reporter receives a fourth invented row with ID 104, amount -250 and status ROW_POSTED in an isolated course copy.

1. In statement-report.c append the record after ID 103. Trace the checked running sum through the fourth row.
2. Use the lesson's two output modes or trace the two writers on paper. Compare the summary and the ID on each output.

**Check your result.** JSON reports postedCount 3 and postedCents 1500. HTML shows Posted total: 1500 cents in 3 entries. Both outputs carry row 104 at -250 cents.

[Step-by-step course guide](../course-guides/bootstrap-native-statements.md) · [Full course](../../courses/bootstrap-native-statements/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/bootstrap-native-statements.md)
