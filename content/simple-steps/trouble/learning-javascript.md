<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-javascript.md

PURPOSE:
Give learners an additional practical case for Learning JavaScript.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep the display when saved JSON is malformed

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice browser exercise displays two notes. Its stored text is the incomplete JSON string {"notes":.

1. Follow the storage lesson’s load path and mark where JSON parsing fails, before the display state would change.
2. Keep the earlier list on a refused load and display a short status in the practice UI. Trace what remains visible.

**Check your result.** The display still has two notes and gives one read error. The incomplete stored value produces no replacement list.

[Step-by-step course guide](../course-guides/learning-javascript.md) · [Full course](../../courses/learning-javascript/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-javascript.md)
