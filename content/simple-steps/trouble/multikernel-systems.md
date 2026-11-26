<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find why a start message is premature

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional worker’s start notification arrives before it completes its own input check.

1. Record the times and identities for start, initialization and ready. Mark the point at which the caller first sends work.
2. Move the work request after a current-worker readiness message and compare the two traces.

**Check your result.** The first trace reaches a starting worker. The corrected trace sends work only after its readiness is recorded.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/multikernel-systems.md)
