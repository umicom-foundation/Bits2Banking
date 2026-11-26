<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-kotlin.md

PURPOSE:
Give learners an additional practical case for Learning Kotlin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a sentinel value with explicit absence

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional queue report gets a real measured count of 0 from one room. The second room supplies no count.

1. Draw one implementation that replaces absence with zero. Draw another with a nullable count as in the course.
2. List the two input rows and compare which implementation allows the caller to recognize absence.

**Check your result.** The first renders both counts as 0. The nullable version retains 0 for the measured count and null for the missing count.

[Step-by-step course guide](../course-guides/learning-kotlin.md) · [Full course](../../courses/learning-kotlin/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-kotlin.md)
