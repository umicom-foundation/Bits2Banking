<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-cmake.md

PURPOSE:
Give learners an additional practical case for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read a CTest failure with its output

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local CTest fixture expects the line count program to report 3, but the program prints 2 for its three-line sample.

1. Run ctest with --output-on-failure in the course build directory and find the failing test's actual output.
2. Check where the program handles the last line and rerun the focused test with `--verbose` after correcting the count.

**Check your result.** The focused test reports Passed and the fixture prints 3.

[Step-by-step course guide](../course-guides/learning-cmake.md) · [Full course](../../courses/learning-cmake/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-cmake.md)
