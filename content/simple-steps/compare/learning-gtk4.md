<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-gtk4.md

PURPOSE:
Give learners an additional practical case for Learning GTK4.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare revealing a panel with running an action

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A GTK scratch preview has a hidden report panel and a Refresh action. The refresh count starts at zero.

1. Trace the discovery lesson’s reveal operation on the panel. Record panel visibility and refresh count.
2. Trace a separate action activation with the panel open. Compare the recorded values to the reveal-only case.

**Check your result.** Revealing shows the panel and keeps the count at zero. Activating Refresh raises the count to one.

[Step-by-step course guide](../course-guides/learning-gtk4.md) · [Full course](../../courses/learning-gtk4/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-gtk4.md)
