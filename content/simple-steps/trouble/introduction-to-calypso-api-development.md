<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/introduction-to-calypso-api-development.md

PURPOSE:
Give learners an additional practical case for Introduction to Calypso API Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a timeout visible in a fake trade lookup

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A two-row practice view loads from a fake repository. On refresh the repository returns a timeout.

1. Record the original row count and request a new read against the fake repository.
2. Show the refresh status separately and check whether the previous rows are still present.

**Check your result.** The view reports timeout and still shows two rows from the last successful read.

[Step-by-step course guide](../course-guides/introduction-to-calypso-api-development.md) · [Full course](../../courses/introduction-to-calypso-api-development/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/introduction-to-calypso-api-development.md)
