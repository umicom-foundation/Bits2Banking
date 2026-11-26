<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/go-statement-tools.md

PURPOSE:
Give learners an additional practical case for Go Statement Tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the CSV amount that cannot be added

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A training CSV has one valid posted amount of 240 cents and another amount written as 4O0 with a letter O.

1. Try to read 4O0 as an integer and note the failing line and field.
2. Record that the row requires correction and check the subtotal of the accepted rows.

**Check your result.** The malformed amount appears in the error record. The accepted subtotal stays at 240 cents.

[Step-by-step course guide](../course-guides/go-statement-tools.md) · [Full course](../../courses/go-statement-tools/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/go-statement-tools.md)
