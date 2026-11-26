<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-php.md

PURPOSE:
Give learners an additional practical case for Learning PHP.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a submitted zero with a field absent from the request

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local PHP form accepts zero for the whole-number field seats. Request A contains seats with the text 0. Request B has no seats field.

1. Use the zero and missing lesson to check presence before any numeric conversion. Record the presence flag in each case.
2. Validate and convert only the present field. Compare the ready value or missing-field status for each request.

**Check your result.** Request A has a supplied value and produces integer 0. Request B has no supplied value and yields a missing-field status.

[Step-by-step course guide](../course-guides/learning-php.md) · [Full course](../../courses/learning-php/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-php.md)
