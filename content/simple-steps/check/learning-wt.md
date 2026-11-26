<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-wt.md

PURPOSE:
Give learners an additional practical case for Learning Wt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that one browser session can end without changing another

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two local Wt session traces start with status Waiting. Session B later displays Report ready.

1. Use the session-lifetime lesson to end session A in one trace after B’s status change. Inspect which state and widgets are destroyed.
2. Repeat from the same starting conditions, this time leaving both sessions open. Check B’s cached status in both traces.

**Check your result.** Closing A destroys its own widget tree. B still shows Report ready in both cases.

[Step-by-step course guide](../course-guides/learning-wt.md) · [Full course](../../courses/learning-wt/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-wt.md)
