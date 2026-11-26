<!--
Umicom Bits2Banking
File: content/simple-steps/check/minix-os-foundations.md

PURPOSE:
Give learners an additional practical case for MINIX OS Foundations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the copy boundary in a small buffer

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local trace models a grant for four writable bytes in a client buffer. The server proposes copies of three and five bytes from offset zero.

1. Draw four buffer positions. Mark how many each proposed copy would overwrite.
2. Use the course transfer contract to record which request is in bounds. Keep the out-of-range result in a separate row.

**Check your result.** The three-byte copy is in bounds. The five-byte request exceeds the grant and must never be accepted as a completed copy.

[Step-by-step course guide](../course-guides/minix-os-foundations.md) · [Full course](../../courses/minix-os-foundations/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/minix-os-foundations.md)
