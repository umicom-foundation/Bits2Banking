<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-data-structures.md

PURPOSE:
Give learners an additional practical case for Learning Data Structures.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Handle undo when the stack is empty

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice editor has no undo records. Pressing Undo should leave the document reading First line.

1. Record the stack size and check whether a record exists before the operation.
2. Run the empty-stack case and compare the document and stack with their original state.

**Check your result.** The stack stays at size zero and the document still reads First line. The action reports that nothing can be undone.

[Step-by-step course guide](../course-guides/learning-data-structures.md) · [Full course](../../courses/learning-data-structures/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-data-structures.md)
