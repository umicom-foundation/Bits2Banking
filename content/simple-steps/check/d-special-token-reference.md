<!--
Umicom Bits2Banking
File: content/simple-steps/check/d-special-token-reference.md

PURPOSE:
Give learners an additional practical case for D Special Tokens for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a build timestamp on replay and rebuild

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper D example prints __TIME__. The first binary captures hypothetical compile time 10:14:05 under the compiler's configured clock. The second is freshly compiled with configured time 10:16:12.

1. Write the output of running the first binary at 10:20:00. Keep its compiled text with the binary.
2. Write the output of running the second binary at the same runtime. Identify which record changes the captured text.

**Check your result.** The first binary still prints 10:14:05 and the fresh binary prints 10:16:12. The new compile changes the captured text.

[Step-by-step course guide](../course-guides/d-special-token-reference.md) · [Full course](../../courses/d-special-token-reference/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/d-special-token-reference.md)
