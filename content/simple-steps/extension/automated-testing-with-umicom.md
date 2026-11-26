<!--
Umicom Bits2Banking
File: content/simple-steps/extension/automated-testing-with-umicom.md

PURPOSE:
Give learners an additional practical case for Automated Testing with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count equal-sized test runs by source

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An outer plan has two planned tests. Tagged output shows outer READ Passed, nested OPEN Passed, nested CLOSE Passed and outer WRITE Skipped. Both runners print progress denominators of two.

1. Mark the two source tags and copy only outer outcomes to the outer result table.
2. Add columns for passed, skipped, failed and missing outcomes. Update them separately from the suite completion status.

**Check your result.** The outer counts are one passed, one skipped, zero failed and zero missing outcomes. A final summary and exit code are still needed to record the suite result.

[Step-by-step course guide](../course-guides/automated-testing-with-umicom.md) · [Full course](../../courses/automated-testing-with-umicom/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/automated-testing-with-umicom.md)
