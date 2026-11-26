<!--
Umicom Bits2Banking
File: content/simple-steps/practice/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate two starting workers

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional report worker is replaced. The original has generation 5 and the replacement has generation 6.

1. Mark generation 6 as starting. Place a late readiness message from generation 5 on its own line.
2. Compare the message identity to the current worker identity before applying it. Then trace a readiness message from generation 6.

**Check your result.** The late message leaves generation 6 unchanged. The current worker’s message can establish its readiness.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Practice by course](index.md)
