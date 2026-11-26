<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/d-special-token-reference.md

PURPOSE:
Give learners an additional practical case for D Special Tokens for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Move a missing helper inside the source boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable D example calls printNote before __EOF__, but the only definition of printNote is after the marker.

1. Mark which part of the source reaches the compiler. Find the call and the hidden definition.
2. Move the single printNote definition above __EOF__ and trace its writeln("note ready") call.

**Check your result.** Before the move the compiler cannot resolve printNote. With the definition in the visible source, the example prints note ready.

[Step-by-step course guide](../course-guides/d-special-token-reference.md) · [Full course](../../courses/d-special-token-reference/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/d-special-token-reference.md)
