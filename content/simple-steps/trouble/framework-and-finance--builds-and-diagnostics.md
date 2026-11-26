<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the callback that survives its window

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper workflow registers an input callback, closes the window and then delivers one queued event. The close path frees the context while its registration is active.

1. Trace the event to the context it tries to use. Mark the context's lifetime on the diagram in Investigate callbacks and window lifetime.
2. Put disconnection before destruction on the same close path, then trace the queued event against the revised lifecycle.

**Check your result.** The first diagram shows an event targeting a freed context. The revised diagram ends the registration before the context is destroyed.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/framework-and-finance--builds-and-diagnostics.md)
