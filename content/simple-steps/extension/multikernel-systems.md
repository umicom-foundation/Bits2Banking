<!--
Umicom Bits2Banking
File: content/simple-steps/extension/multikernel-systems.md

PURPOSE:
Give learners an additional practical case for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Set a restart observation limit for two jobs

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice service observes two workers. Only the report worker timed out.

1. Write an identity, latest observation and recovery decision for each worker. Keep the currently healthy worker in its own row.
2. Trace one restart of the timed-out worker and write which generation should supply the next ready signal.

**Check your result.** The recovery action affects the timed-out worker only. The other worker’s last result stays usable.

[Step-by-step course guide](../course-guides/multikernel-systems.md) · [Full course](../../courses/multikernel-systems/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/multikernel-systems.md)
