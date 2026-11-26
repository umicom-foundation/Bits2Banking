<!--
Umicom Bits2Banking
File: content/simple-steps/compare/d-special-token-reference.md

PURPOSE:
Give learners an additional practical case for D Special Tokens for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a source cutoff with a function return

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An offline D fixture contains two declarations that share the same name, with __EOF__ between them. A second fixture places return inside a running function and keeps both declarations in the same visible scope.

1. Mark which declarations reach compilation in each fixture.
2. Write when the scanner marker and the return have their effect. Use the duplicate declaration as the visible compiler outcome.

**Check your result.** The scanner fixture submits just the first declaration. The return fixture still submits both declarations and is rejected for the duplicate.

[Step-by-step course guide](../course-guides/d-special-token-reference.md) · [Full course](../../courses/d-special-token-reference/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/d-special-token-reference.md)
