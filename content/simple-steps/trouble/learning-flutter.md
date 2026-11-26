<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-flutter.md

PURPOSE:
Give learners an additional practical case for Learning Flutter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Trace a callback after disposal

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice screen starts a delayed status update, then the test closes the screen before the update becomes ready.

1. In the state and disposal lesson, mark the point when the screen’s state is disposed. Draw the delayed callback after that point.
2. Use the lesson’s mounted check before the callback requests a rebuild. Keep a tally for the screen that has already closed.

**Check your result.** The tally for the disposed screen stays at zero and the trace reaches no state update after it closes.

[Step-by-step course guide](../course-guides/learning-flutter.md) · [Full course](../../courses/learning-flutter/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-flutter.md)
