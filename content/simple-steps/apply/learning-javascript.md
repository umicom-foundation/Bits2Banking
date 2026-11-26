<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-javascript.md

PURPOSE:
Give learners an additional practical case for Learning JavaScript.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Display a checked result through a single rendering path

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local diagnostic panel needs to display either Ready 7 or Unable to prepare report, depending on an invented result object.

1. Use the document-updates lesson to choose a status message from a checked success flag and value.
2. Render that message with textContent in one status element. Feed a success fixture with 7 followed by the refusal fixture.

**Check your result.** The same status element first reads Ready 7 and then Unable to prepare report. The refusal does not reuse the number 7.

[Step-by-step course guide](../course-guides/learning-javascript.md) · [Full course](../../courses/learning-javascript/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-javascript.md)
