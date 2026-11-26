<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/building-blockchain-from-scratch.md

PURPOSE:
Provide practical first steps and a result to check for Building Blockchain from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Building Blockchain from Scratch

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Write a practice record with sequence 1 and amount 1,000. Give each field four little-endian bytes. [An exact record format](../../courses/building-blockchain-from-scratch/lessons/01-an-exact-record-format.html)
2. Encode sequence 2 and amount 256. Check each field independently before joining the eight bytes. [An exact record format](../../courses/building-blockchain-from-scratch/lessons/01-an-exact-record-format.html)
3. Trace the balance check in the next lesson with a request for more than the current balance. [Validate before changing state](../../courses/building-blockchain-from-scratch/lessons/02-validate-before-changing-state.html)

**Check your result.** The second record is `02 00 00 00 00 01 00 00`. An unaffordable request leaves the balance unchanged.

[Continue in the full course](../../courses/building-blockchain-from-scratch/index.html) · [All course guides](index.md)
