<!--
Umicom Bits2Banking
File: content/simple-steps/check/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check event delivery before and after cleanup

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An offline window fixture starts with one live registered callback. Case A delivers an event before close. Case B delivers a new event after disconnection and destruction.

1. Write the two checkpoints using the lifetime diagram. Begin a separate callback counter for the event in each case.
2. Define pass conditions that include the object's ownership state alongside the count.

**Check your result.** Case A delivers one callback while the context is alive. Case B delivers zero callbacks and accesses the destroyed context zero times.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/framework-and-finance--builds-and-diagnostics.md)
