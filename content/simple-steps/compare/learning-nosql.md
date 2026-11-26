<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-nosql.md

PURPOSE:
Give learners an additional practical case for Learning NoSQL and MongoDB.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a requested field list with the whole record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional document has ID R5, status Ready, and an internal training note Sample review.

1. Use the query lesson to trace a whole-document read. Check which fields reach a display component if it uses that result directly.
2. Trace a projection restricted to ID and status. Make a short list of both returned field sets.

**Check your result.** The whole record contains all three fields. The restricted result contains ID R5 and status Ready without the training note.

[Step-by-step course guide](../course-guides/learning-nosql.md) · [Full course](../../courses/learning-nosql/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-nosql.md)
