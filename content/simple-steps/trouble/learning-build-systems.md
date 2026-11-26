<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the absent definition during a link

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice target produces main.o and helper.o, but its link command names only main.o. The call to report_count remains unresolved.

1. Compare the object inputs in the link command with the object that defines report_count.
2. Add helper.o as a target input and rerun the local build.

**Check your result.** Both object files are passed to the linker, and the link completes with report_count resolved.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-build-systems.md)
