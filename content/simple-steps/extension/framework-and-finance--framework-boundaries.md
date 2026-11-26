<!--
Umicom Bits2Banking
File: content/simple-steps/extension/framework-and-finance--framework-boundaries.md

PURPOSE:
Give learners an additional practical case for Introduction to Umicom Framework Architecture.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a borrowed name alive in a report

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A training C service lends a pointer to a temporary name buffer. The caller needs to keep the name Birch after that buffer is reused for Oak.

1. Make an owned copy of Birch while the borrowed pointer is valid.
2. Reuse the service buffer for Oak and print the saved copy and the latest service name.

**Check your result.** The saved report still reads Birch. The current service name reads Oak.

[Step-by-step course guide](../course-guides/framework-and-finance--framework-boundaries.md) · [Full course](../../courses/framework-and-finance/framework-boundaries/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/framework-and-finance--framework-boundaries.md)
