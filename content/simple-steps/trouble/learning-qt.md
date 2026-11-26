<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-qt.md

PURPOSE:
Give learners an additional practical case for Learning Qt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find which input route uses the rule

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice dialog’s button increases a displayed count. The keyboard action has been wired only to a visual label.

1. Find the button connection and the keyboard action in the signals-and-callbacks lesson. Trace each into the shared rule.
2. Route the keyboard action to the same rule in a scratch diagram. Begin at zero and trace one click followed by one key action.

**Check your result.** The corrected diagram reaches the shared rule twice and displays counts 1 and 2 in that order.

[Step-by-step course guide](../course-guides/learning-qt.md) · [Full course](../../courses/learning-qt/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-qt.md)
