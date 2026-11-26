<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/building-bitcoin-in-c.md

PURPOSE:
Give learners an additional practical case for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a short little-endian span

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A lesson helper is asked to read four bytes at offset 1 from the four-byte array 78 56 34 12, shown in hex. The result begins at 42.

1. Subtract the offset from the length, then compare the remaining byte count with the required four.
2. Trace read_u32_le to its first return and check the assignment to the result separately.

**Check your result.** The helper sees three available bytes, returns false and leaves the result at 42.

[Step-by-step course guide](../course-guides/building-bitcoin-in-c.md) · [Full course](../../courses/building-bitcoin-in-c/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/building-bitcoin-in-c.md)
