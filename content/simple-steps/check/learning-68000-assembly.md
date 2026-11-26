<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-68000-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 68000 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a bounded loop before its first write

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A 68000 worksheet writes consecutive byte values starting at 1, with a guard that tests the remaining count before every write.

1. Start the first case with a count of zero and record which memory positions are written.
2. Start a fresh second case with a count of two and trace each write before the count reaches zero.

**Check your result.** The zero case writes no bytes. The second case writes the values 1 and 2, then stops.

[Step-by-step course guide](../course-guides/learning-68000-assembly.md) · [Full course](../../courses/learning-68000-assembly/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-68000-assembly.md)
