<!--
Umicom Bits2Banking
File: content/simple-steps/check/introduction-to-calypso-api-development.md

PURPOSE:
Give learners an additional practical case for Introduction to Calypso API Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the statuses of found and missing trades

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fake local Java repository has one trade with ID Q9. A teaching service distinguishes a found record from a missing one.

1. Request Q9 and record the status and returned trade ID.
2. Request Q10 from the same repository and check whether the result includes a payload.

**Check your result.** Q9 returns found with ID Q9. Q10 returns missing with an empty payload.

[Step-by-step course guide](../course-guides/introduction-to-calypso-api-development.md) · [Full course](../../courses/introduction-to-calypso-api-development/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/introduction-to-calypso-api-development.md)
