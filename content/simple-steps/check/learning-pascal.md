<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-pascal.md

PURPOSE:
Give learners an additional practical case for Learning Pascal.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that a refused edit preserves the notebook

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch name policy allows four or fewer characters. A notebook initially contains Ada in its only occupied slot.

1. From the notebook validation lesson, write one case changing the name to Elm and another changing it to Cedars. Begin each case with the unchanged Ada fixture.
2. Check both the returned status and which name remains stored after each attempt. Keep the occupied count in the record.

**Check your result.** Elm is accepted and becomes the stored name. Cedars is refused and Ada remains. Both cases retain one occupied slot.

[Step-by-step course guide](../course-guides/learning-pascal.md) · [Full course](../../courses/learning-pascal/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-pascal.md)
