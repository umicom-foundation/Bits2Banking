<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-bitcoin-in-c.md

PURPOSE:
Give learners an additional practical case for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a word after a one-byte prefix

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A six-byte teaching buffer has hex bytes AA 78 56 34 12 BB. The field begins at offset 1.

1. Write the four admitted bytes and label their shifts as 0, 8, 16 and 24 bits.
2. Apply read_u32_le and compare the computed word with the result of incorrectly starting at offset zero.

**Check your result.** The offset-one read succeeds with 0x12345678. The offset-zero read would produce 0x345678AA, showing why the field offset matters.

[Step-by-step course guide](../course-guides/building-bitcoin-in-c.md) · [Full course](../../courses/building-bitcoin-in-c/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-bitcoin-in-c.md)
