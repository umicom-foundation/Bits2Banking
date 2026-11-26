<!--
Umicom Bits2Banking
File: content/simple-steps/practice/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find exactly what a change includes

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice notes repository has a tracked README and an untracked temporary output.

1. Run `git status --short` in the practice directory. Identify the output file and edit one line of the README.
2. Use `git diff -- README.md` and compare the result with the file list. Keep the temporary output as a separate observation.

**Check your result.** The README diff shows the line edit. The output appears only in the list of untracked files.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Practice by course](index.md)
