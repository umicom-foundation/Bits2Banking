<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-nosql.md

PURPOSE:
Give learners an additional practical case for Learning NoSQL and MongoDB.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check duplicate identity without confusing it with a repeated label

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch collection has a unique ID index and one record R1 labelled Gallery.

1. Trace adding R1 labelled Studio in a fresh test. Then reset the fixture and trace adding R2 labelled Gallery.
2. Check the number of stored records and the accepted or refused result in both cases.

**Check your result.** The repeated ID is refused and leaves one record. The repeated label on a new ID is accepted and leaves two.

[Step-by-step course guide](../course-guides/learning-nosql.md) · [Full course](../../courses/learning-nosql/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-nosql.md)
