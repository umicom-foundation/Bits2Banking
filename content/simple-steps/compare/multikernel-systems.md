<!--
Umicom Bits2Banking
File: content/simple-steps/compare/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a copied message with an owned buffer

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A classroom controller sends a small readiness value to a worker. A second example also supplies a larger buffer with an identified owner.

1. Draw the two message shapes and write which component may release the larger storage. Mark what the receiver reads.
2. Check how each can be retained after sending. Record what must remain alive in the buffer case.

**Check your result.** The copied message carries its own small value. The buffer case still depends on its agreed lifetime and ownership.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/multikernel-systems.md)
