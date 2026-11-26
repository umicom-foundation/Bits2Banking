<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-gtk4.md

PURPOSE:
Give learners an additional practical case for Learning GTK4.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a count visible when an edit is refused

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A GTK practice window already displays 9 visitors. The next text input contains an invalid count.

1. Use the event-handling lesson to draw the input callback and mark the point where it receives a validation result.
2. Plan a success branch that updates the count label and a refusal branch that updates only a separate status label. Trace the rejected input on paper.

**Check your result.** The count label still reads 9 and the status reads Enter a whole-number count.

[Step-by-step course guide](../course-guides/learning-gtk4.md) · [Full course](../../courses/learning-gtk4/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-gtk4.md)
