<!--
Umicom Bits2Banking
File: content/simple-steps/check/go-statement-tools.md

PURPOSE:
Give learners an additional practical case for Go Statement Tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that CSV rows match their header width

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two separate CSV fixtures use the same header id,status,amount. The first has a three-field row W1,posted,80. The second appends a fourth extra field to the same row.

1. Read the first fixture using the course's column count rule and record the accepted row count.
2. Read the second fixture with the same rule and capture the field-count error before applying its row.

**Check your result.** The first fixture contributes one row for W1. The second reports a field-count error and contributes zero rows.

[Step-by-step course guide](../course-guides/go-statement-tools.md) · [Full course](../../courses/go-statement-tools/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/go-statement-tools.md)
