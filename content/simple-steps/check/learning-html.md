<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-html.md

PURPOSE:
Give learners an additional practical case for Learning HTML.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check data text stays out of markup

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The local table exercise needs one cell containing Elm and one containing the literal label `Room <West>`.

1. Write the two expected text values first. Use the record-text lesson to populate both cells by treating their contents as text.
2. Inspect the visible cells and the locally parsed element tree. Check whether either value added an unexpected child element.

**Check your result.** The cells display Elm and `Room <West>`. Neither cell contains a child element created from its text.

[Step-by-step course guide](../course-guides/learning-html.md) · [Full course](../../courses/learning-html/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-html.md)
