<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-6800-assembly.md

PURPOSE:
Give learners an additional practical case for Learning Motorola 6800 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an addition that wraps after FF

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

On paper, the 6800 accumulator starts at hexadecimal FF and an addition contributes hexadecimal 01.

1. Add the values and preserve the carry out of the lowest eight bits.
2. Write the low eight bits into the accumulator column and mark the carry flag.

**Check your result.** The accumulator holds hexadecimal 00 and carry is set.

[Step-by-step course guide](../course-guides/learning-6800-assembly.md) · [Full course](../../courses/learning-6800-assembly/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-6800-assembly.md)
