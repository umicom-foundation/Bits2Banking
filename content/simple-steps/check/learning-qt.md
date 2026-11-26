<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-qt.md

PURPOSE:
Give learners an additional practical case for Learning Qt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an edit from the correct and incorrect thread

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice Qt model owns one record with title Elm. A proposed edit changes it to Oak.

1. Use the owner-thread lesson to put one test edit on the model’s owning thread. Trace it through the normal publish step.
2. Reset the fixture and trace an attempted direct mutation from a non-owner thread. Keep that attempt as a paper test of the adapter guard.

**Check your result.** The owner-thread change publishes Oak once. The direct non-owner attempt is refused by the scratch guard and leaves Elm in the model.

[Step-by-step course guide](../course-guides/learning-qt.md) · [Full course](../../courses/learning-qt/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-qt.md)
