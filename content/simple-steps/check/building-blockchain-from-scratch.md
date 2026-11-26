<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-blockchain-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Blockchain from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an independently recorded chain head

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An offline lesson fixture keeps one trusted reference digest. A saved chain with original record amounts is replayed first. A second copy changes an earlier amount from 15 to 16.

1. Trace where the changed bytes enter the hash input and where their digest enters the later record.
2. Write the two outcomes against the same trusted reference. Keep the decision limited to record integrity.

**Check your result.** The original replay matches the reference head. The altered replay produces a mismatch under the lab's integrity check.

[Step-by-step course guide](../course-guides/building-blockchain-from-scratch.md) · [Full course](../../courses/building-blockchain-from-scratch/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-blockchain-from-scratch.md)
