<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-cmake.md

PURPOSE:
Give learners an additional practical case for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare one requested build target with the default build set

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A clean CMake practice graph has a library called numbers and two executables named report and quiz. Only report depends on numbers, and all three are default targets.

1. Build report by name in the first empty build directory and record the targets produced.
2. Request the default build in a second empty build directory configured from the same source.

**Check your result.** The first build produces numbers and report. The default build also produces quiz.

[Step-by-step course guide](../course-guides/learning-cmake.md) · [Full course](../../courses/learning-cmake/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-cmake.md)
