<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-68000-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 68000 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Fill three entries in a memory strip

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper 68000 program uses D0 for a byte value, A0 for a destination address, and three reserved bytes beginning at hexadecimal 2000.

1. Start D0 at hexadecimal 02 and A0 at hexadecimal 2000. Repeat three times, writing the low byte of D0 and advancing the address before incrementing the value.
2. Read back the three bytes in address order and record where A0 points after the last iteration.

**Check your result.** The three bytes hold hexadecimal 02, 03 and 04. A0 points to hexadecimal 2003.

[Step-by-step course guide](../course-guides/learning-68000-assembly.md) · [Full course](../../courses/learning-68000-assembly/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-68000-assembly.md)
