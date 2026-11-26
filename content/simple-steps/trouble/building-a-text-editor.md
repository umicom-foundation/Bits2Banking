<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/building-a-text-editor.md

PURPOSE:
Give learners an additional practical case for Building a Text Editor in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Erase a count from a position

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The C editor contains ABCDE. A learner types erase 1 3 expecting to remove the bytes at positions 1 and 2 only.

1. Use Insert and erase text without losing the tail to mark the starting index and the next three bytes.
2. In a spare editor session run append ABCDE, erase 1 3 and show on separate lines, then discard.

**Check your result.** The removed bytes are BCD. The show command prints TEXT: AE.

[Step-by-step course guide](../course-guides/building-a-text-editor.md) · [Full course](../../courses/building-a-text-editor/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/building-a-text-editor.md)
