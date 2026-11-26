<!--
Umicom Bits2Banking
File: content/simple-steps/extension/mongodb-c23-documents.md

PURPOSE:
Give learners an additional practical case for MongoDB Receipt Documents in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Report present and omitted fields separately

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two fictional receipts contain identifiers R2 and R3. R2 has a recorded surcharge of 50 cents and R3 omits it.

1. Add the proper field representation to a local fixture for R2. Leave it absent for the second receipt.
2. Use the existing typed field check to make a report with columns for identity, presence and value.

**Check your result.** R2 shows present and 50 cents. R3 shows absent and no numeric amount.

[Step-by-step course guide](../course-guides/mongodb-c23-documents.md) · [Full course](../../courses/mongodb-c23-documents/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/mongodb-c23-documents.md)
