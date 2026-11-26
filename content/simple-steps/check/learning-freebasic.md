<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-freebasic.md

PURPOSE:
Give learners an additional practical case for Learning FreeBASIC.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that an array grows without losing stored entries

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local FreeBASIC array starts with indexes 1 through 2, storing 11 and 19. The edit grows it to index 3.

1. Following the dynamic-array lesson, write a case that grows the array with preservation and then writes value 25 at index 3.
2. Reset the fixture. Grow it without preservation, then inspect the first two entries before writing the same new value.

**Check your result.** With preservation the entries are 11, 19, and 25. Without it the first two numeric entries are reinitialized to zero.

[Step-by-step course guide](../course-guides/learning-freebasic.md) · [Full course](../../courses/learning-freebasic/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-freebasic.md)
