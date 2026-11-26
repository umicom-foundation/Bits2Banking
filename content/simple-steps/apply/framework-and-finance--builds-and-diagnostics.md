<!--
Umicom Bits2Banking
File: content/simple-steps/apply/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Write a bug report for one event after close

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local mock window closes after receiving one input event. A second event arrives while the window object is still owned but its callback should already be disconnected.

1. Create a reproducible paper timeline for create, register, event, disconnect, close and late event.
2. Put expected callbacks and observed callbacks in separate columns. Write the single pass condition for the late event.

**Check your result.** The expected count is one callback before disconnection and zero from the late event. The report has a separate place to attach observed evidence.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Small projects by course](index.md) · [First practice case](../practice/framework-and-finance--builds-and-diagnostics.md)
