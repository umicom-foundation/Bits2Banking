<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/accessible-statement-review.md

PURPOSE:
Give learners an additional practical case for Accessible Statement Review.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Repair a checkbox label

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Clicking the text Show only posted rows above a local statement no longer selects its checkbox after a learner moved the checkbox outside the label.

1. Find the checkbox id and add that exact spelling to the label's for attribute.
2. Reload statement.html. Click the text, then press Space while the checkbox has focus.

**Check your result.** Clicking the label selects the checkbox and shows two rows. Space clears it and restores all three.

[Step-by-step course guide](../course-guides/accessible-statement-review.md) · [Full course](../../courses/accessible-statement-review/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/accessible-statement-review.md)
