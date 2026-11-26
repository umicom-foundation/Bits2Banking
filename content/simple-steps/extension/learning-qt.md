<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-qt.md

PURPOSE:
Give learners an additional practical case for Learning Qt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Resize a view without changing its data

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Qt room summary shows 6 accepted records and the learner wants more space around the label.

1. Use the layout and ownership lesson to find a layout margin option for the summary view. Keep the accepted count in the existing model.
2. Trace the same count through a narrow and a wide layout. Record which object owns the data and which arranges the label.

**Check your result.** The margin changes in the view and the model still supplies count 6 in both layouts.

[Step-by-step course guide](../course-guides/learning-qt.md) · [Full course](../../courses/learning-qt/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-qt.md)
