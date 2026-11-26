<!--
Umicom Bits2Banking
File: content/simple-steps/practice/mongodb-c23-documents.md

PURPOSE:
Give learners an additional practical case for MongoDB Receipt Documents in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a field type before displaying a result

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional receipt stores 1,500 as an integer number of cents. A changed copy stores `1500` as text.

1. Write the expected field name and integer type. Trace each value through the course’s BSON reader example.
2. Record when the receipt can be displayed and when the unexpected representation needs review.

**Check your result.** Only the integer field meets the exercise’s contract. The text copy keeps its type failure visible.

[Step-by-step course guide](../course-guides/mongodb-c23-documents.md) · [Full course](../../courses/mongodb-c23-documents/index.html) · [Practice by course](index.md)
