<!--
Umicom Bits2Banking
File: content/simple-steps/apply/d-keyword-reference.md

PURPOSE:
Give learners an additional practical case for D Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Capture a failure and finish its review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional D job reviews a receipt whose cents field is absent. The project needs a short console trace that shows both the problem and completion of the review.

1. Adapt the lesson's try, catch and finally example. Keep the throw in the missing-amount branch and use the message missing amount.
2. Write review finished in finally. Trace which messages appear for the missing-amount input and in what order.

**Check your result.** The error handler reports missing amount first. The cleanup message review finished follows it once.

[Step-by-step course guide](../course-guides/d-keyword-reference.md) · [Full course](../../courses/d-keyword-reference/index.html) · [Small projects by course](index.md) · [First practice case](../practice/d-keyword-reference.md)
