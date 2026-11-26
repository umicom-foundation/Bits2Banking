<!--
Umicom Bits2Banking
File: content/simple-steps/compare/safer-c-programming.md

PURPOSE:
Give learners an additional practical case for Safer C Programming.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare copying inside and outside an overlapping range

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A training buffer holds six bytes. A second region begins two bytes after the first in one scenario and beyond it in the other.

1. Draw source and destination byte positions for a three-byte transfer. Mark whether the spans overlap.
2. Use the course’s copy selection discussion to record which contract handles overlap.

**Check your result.** The first placement shares a byte with the source. The move contract can cover overlap while a non-overlapping copy requires disjoint regions.

[Step-by-step course guide](../course-guides/safer-c-programming.md) · [Full course](../../courses/safer-c-programming/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/safer-c-programming.md)
