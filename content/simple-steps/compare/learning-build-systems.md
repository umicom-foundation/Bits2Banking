<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare timestamps with a content record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fixture has two versions of settings.h with the same recorded modification time. Their only lines are #define MODE 1 and #define MODE 2 respectively.

1. Compare the recorded times and decide what a timestamp-only comparison observes.
2. Compare file hashes computed over the two fixtures with the lesson's file identity tool.

**Check your result.** The timestamp values match. The two content hashes differ.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-build-systems.md)
