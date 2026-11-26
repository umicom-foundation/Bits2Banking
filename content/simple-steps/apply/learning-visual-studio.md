<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-visual-studio.md

PURPOSE:
Give learners an additional practical case for Learning Visual Studio for Umicom development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Pair a compiler build with its run record

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A sample qualification record needs to show which debug build supplied the Umicom C executable that printed its version.

1. Follow the guide’s terminal build section and record the named configure and build preset beside the executable path from its launch command.
2. Add the configure and build statuses for the same successful fixture run. Attach its version output to that executable path.

**Check your result.** The record pairs windows-ucrt64-debug with the executable in that preset’s bin directory and keeps one version line from the same launch.

[Step-by-step course guide](../course-guides/learning-visual-studio.md) · [Full course](../../courses/learning-visual-studio/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-visual-studio.md)
