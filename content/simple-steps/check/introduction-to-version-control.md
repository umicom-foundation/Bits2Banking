<!--
Umicom Bits2Banking
File: content/simple-steps/check/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check whether a branch can move forward without merging histories

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two paper commit graphs start at A. The first has local A and incoming A followed by B. The second has local A followed by C and incoming A followed by B.

1. In the first graph, trace the incoming history and mark whether it contains the local tip.
2. Repeat with the second graph and record whether a fast-forward would be permitted.

**Check your result.** The first can move to B by fast-forward. The second has two distinct tips and fails the fast-forward check.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/introduction-to-version-control.md)
