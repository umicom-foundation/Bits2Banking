<!--
Umicom Bits2Banking
File: content/simple-steps/compare/mongodb-c23-documents.md

PURPOSE:
Give learners an additional practical case for MongoDB Receipt Documents in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a stored amount with converted text

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One toy document has integer 610 cents. A second has the characters `610`.

1. Write both BSON field types and trace the exact field inspection step.
2. If the course permits an explicit conversion in a separate stage, write where that would occur and keep the type observations separate.

**Check your result.** The integer satisfies the immediate numeric field check. The text requires its own handling before it becomes a numeric value.

[Step-by-step course guide](../course-guides/mongodb-c23-documents.md) · [Full course](../../courses/mongodb-c23-documents/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/mongodb-c23-documents.md)
