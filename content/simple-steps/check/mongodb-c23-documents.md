<!--
Umicom Bits2Banking
File: content/simple-steps/check/mongodb-c23-documents.md

PURPOSE:
Give learners an additional practical case for MongoDB Receipt Documents in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a present field and unexpected representation

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A toy document reports a signed cents field as integer 0. A second reports it as the string `zero`.

1. Write the required type from the course. Use the field reader on both types without converting them first.
2. Record the observed presence and the type result separately for each document.

**Check your result.** Both fields are present. Only the integer 0 meets the stated type contract.

[Step-by-step course guide](../course-guides/mongodb-c23-documents.md) · [Full course](../../courses/mongodb-c23-documents/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/mongodb-c23-documents.md)
