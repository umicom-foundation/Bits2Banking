<!--
Umicom Bits2Banking
File: content/simple-steps/check/automated-testing-with-umicom.md

PURPOSE:
Give learners an additional practical case for Automated Testing with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a test prefix at the newline boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The plan selects two tests. Capture A contains only the text 1/2 Test #8: ready .... Passed 0.01 sec with no final line feed. Capture B is the identical text followed by a line feed.

1. Use Check complete rows in a saved prefix to mark which capture has a complete result row.
2. Trace the reported status, pass count and observed-result count, keeping an earlier summary in place until a new one is accepted.

**Check your result.** Capture A returns UMI_STATUS_NOT_FOUND and keeps the earlier summary. Capture B publishes one observed result and one pass against the two planned tests.

[Step-by-step course guide](../course-guides/automated-testing-with-umicom.md) · [Full course](../../courses/automated-testing-with-umicom/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/automated-testing-with-umicom.md)
