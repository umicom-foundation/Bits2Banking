<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-a-compiler-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two ways of reading the instruction count

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two eight-byte UMCB headers have identical magic, version and flags. One ends with the hex bytes 02 00 and the other with 00 02.

1. Apply the little-endian rule to the count bytes in each header.
2. Calculate the declared file length using eight header bytes and nine bytes per declared instruction. Record the numbers before applying any execution limit.

**Check your result.** 02 00 declares 2 instructions and 26 bytes. 00 02 declares 512 instructions and 4,616 bytes.

[Step-by-step course guide](../course-guides/building-a-compiler-in-c.md) · [Full course](../../courses/building-a-compiler-in-c/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-a-compiler-in-c.md)
