<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/cpp20-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C++20 Keyword and Token Reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace an accidental fall-through

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice C++ switch handles code 7 by assigning score = 2. Its default assigns score = 0, and the case 7 block ends without break.

1. Trace code 7 through the two assignments as the switch is written.
2. Add break directly after score = 2 in a practice copy. Trace code 7 and code 9 again.

**Check your result.** Before the change, code 7 ends with score 0. After the change, code 7 ends with 2 and code 9 ends with 0.

[Step-by-step course guide](../course-guides/cpp20-keyword-reference.md) · [Full course](../../courses/cpp20-keyword-reference/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/cpp20-keyword-reference.md)
