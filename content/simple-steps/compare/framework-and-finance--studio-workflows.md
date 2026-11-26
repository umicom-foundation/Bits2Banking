<!--
Umicom Bits2Banking
File: content/simple-steps/compare/framework-and-finance--studio-workflows.md

PURPOSE:
Give learners an additional practical case for Learning Studio Documents and Visual Design.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a tool's output with its exit status

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two supplied process records each say Report ready in standard output. The first has exit status 0. The second has exit status 2 and an error line in standard error.

1. Read the exit value and identify the stream that contains the error line.
2. Mark whether each record can be credited as a successful process result under a zero-only success rule.

**Check your result.** The status 0 record is accepted. The status 2 record is flagged as failed even though it contains Report ready.

[Step-by-step course guide](../course-guides/framework-and-finance--studio-workflows.md) · [Full course](../../courses/framework-and-finance/studio-workflows/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/framework-and-finance--studio-workflows.md)
