<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-kotlin.md

PURPOSE:
Give learners an additional practical case for Learning Kotlin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep conversion and range checks separate

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A training program accepts seat numbers from 1 through 30. One caller enters 31 and another enters seven.

1. Trace the whole-number conversion used by the command-line lesson. Give each input its own row in a test table.
2. Apply the 1 through 30 rule only after conversion succeeds. Write a distinct message for each refusal.

**Check your result.** 31 is a valid integer and fails the range check. seven fails conversion and reaches no range check.

[Step-by-step course guide](../course-guides/learning-kotlin.md) · [Full course](../../courses/learning-kotlin/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-kotlin.md)
