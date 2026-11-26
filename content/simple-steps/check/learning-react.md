<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-react.md

PURPOSE:
Give learners an additional practical case for Learning React.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that editing the input does not submit it

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch React component displays an input draft and a separate saved value Elm. Its Submit action copies the draft once in this fixture.

1. Write a control test that enters Oak and reads the two views before pressing Submit.
2. Starting from that draft, press Submit once and check the two views and the number of save calls.

**Check your result.** Editing shows Oak in the input while the saved view stays Elm and records zero saves. Submitting shows Oak in both views and records one save.

[Step-by-step course guide](../course-guides/learning-react.md) · [Full course](../../courses/learning-react/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-react.md)
