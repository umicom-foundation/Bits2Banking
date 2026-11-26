<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/banking-technology-foundations.md

PURPOSE:
Give learners an additional practical case for Banking Technology Foundations.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep currency in the matching key

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local row reads P84 USD 600 and one statement row reads P84 EUR 600. An amount-only check marks the payment reconciled.

1. Write each row as a three-part record with reference, currency and cents.
2. Compare the pair of identity fields before comparing cents. Mark the local row and the statement row independently.

**Check your result.** The USD row has no matching statement row and the EUR row has no matching local row. There are zero reconciled rows.

[Step-by-step course guide](../course-guides/banking-technology-foundations.md) · [Full course](../../courses/banking-technology-foundations/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/banking-technology-foundations.md)
