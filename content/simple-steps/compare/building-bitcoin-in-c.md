<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-bitcoin-in-c.md

PURPOSE:
Give learners an additional practical case for Building Bitcoin from Scratch Using Assembly and C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the reader's contract with a raw machine load

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper caller presents three bytes from a Bitcoin teaching buffer. Compare read_u32_le with the illustrative assembly load, whose precondition requires four valid bytes.

1. Trace the available-byte check in the C function. Mark whether it reaches the four-byte read.
2. Write the assembly helper's precondition on the caller card. Mark whether the same input can be passed to it.

**Check your result.** The C helper returns false before reading a word. The assembly caller must refuse this input before calling the helper because only three bytes are available.

[Step-by-step course guide](../course-guides/building-bitcoin-in-c.md) · [Full course](../../courses/building-bitcoin-in-c/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-bitcoin-in-c.md)
