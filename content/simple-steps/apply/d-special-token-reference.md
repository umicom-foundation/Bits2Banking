<!--
Umicom Bits2Banking
File: content/simple-steps/apply/d-special-token-reference.md

PURPOSE:
Give learners an additional practical case for D Special Tokens for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Make a source map for two generated lines

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A D code generator produces local report.d from a fictional source sheet called account_rules.d. Two emitted print statements come from rules 18 and 44.

1. In a scratch copy, add a #line directive before each statement as shown in Map a diagnostic back to source.
2. Use the following statement's source-location values to make a two-row map and check the printed file name for each.

**Check your result.** The mapped locations are account_rules.d line 18 and account_rules.d line 44, in that order.

[Step-by-step course guide](../course-guides/d-special-token-reference.md) · [Full course](../../courses/d-special-token-reference/index.html) · [Small projects by course](index.md) · [First practice case](../practice/d-special-token-reference.md)
