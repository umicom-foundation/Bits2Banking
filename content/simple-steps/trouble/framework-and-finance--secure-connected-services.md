<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/framework-and-finance--secure-connected-services.md

PURPOSE:
Give learners an additional practical case for Introduction to Secure Connected Services.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a failed write from advancing a record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a local test fixture, a draft starts in revision 2. The fake store returns a write failure when asked to save revision 3.

1. Record the draft revision before the save and the store result after the attempt.
2. Reload the committed revision from the fake store and check what the caller sees.

**Check your result.** The caller receives a failure, and the reloaded draft remains at revision 2.

[Step-by-step course guide](../course-guides/framework-and-finance--secure-connected-services.md) · [Full course](../../courses/framework-and-finance/secure-connected-services/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/framework-and-finance--secure-connected-services.md)
