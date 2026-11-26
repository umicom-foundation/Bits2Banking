<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-linux-development.md

PURPOSE:
Give learners an additional practical case for Learning Linux Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Put results and diagnostics in separate files

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local fixture writes accepted 4 to standard output and source unavailable to standard error.

1. Using the process lesson, redirect standard output to result.txt and standard error to diagnostic.txt in a scratch folder.
2. Read both files separately and check that neither contains the other stream’s line.

**Check your result.** result.txt contains accepted 4 on its own line. diagnostic.txt contains source unavailable on its own line.

[Step-by-step course guide](../course-guides/learning-linux-development.md) · [Full course](../../courses/learning-linux-development/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-linux-development.md)
