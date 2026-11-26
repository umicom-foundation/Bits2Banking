<!--
Umicom Bits2Banking
File: content/simple-steps/check/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check whether a worker can accept a task

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One mock worker reports ready for its current generation. Another reports only that startup began.

1. Prepare a table with current identity, reported state and expected admission. Keep the requested task identical.
2. Trace the acceptance rule separately for each worker and record any work not sent.

**Check your result.** Only the worker with the current ready signal receives the task under the exercise’s rule.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/multikernel-systems.md)
