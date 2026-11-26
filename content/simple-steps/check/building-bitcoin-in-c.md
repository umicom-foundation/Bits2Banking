<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-bitcoin-in-c.md

PURPOSE:
Give learners an additional practical case for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the final legal start of a wire field

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two offline reader cases pass length 6 and the bytes 00 00 21 43 65 87 in hex. The first uses offset 2 and the second uses offset 7. Result is initially 42 in each case.

1. Apply the offset-greater-than-length check before subtracting. Work out how many bytes remain in the admitted case.
2. Compute the unsigned value for the admitted case and record the result slot after both calls.

**Check your result.** Offset 2 has exactly four bytes and returns true with 0x87654321. Offset 7 returns false and leaves 42.

[Step-by-step course guide](../course-guides/building-bitcoin-in-c.md) · [Full course](../../courses/building-bitcoin-in-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-bitcoin-in-c.md)
