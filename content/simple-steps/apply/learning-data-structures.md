<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-data-structures.md

PURPOSE:
Give learners an additional practical case for Learning Data Structures.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record a task order with a queue and an undo record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper work list starts with Measure and Record. The user completes Measure, then immediately undoes that completion.

1. Use a queue for pending tasks and an undo stack for completed items. Place the completed task on the stack after taking it from the front.
2. Pop the saved completion and use it to restore Measure to the front of the pending list.

**Check your result.** The pending list again reads Measure followed by Record, and the undo stack is empty.

[Step-by-step course guide](../course-guides/learning-data-structures.md) · [Full course](../../courses/learning-data-structures/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-data-structures.md)
