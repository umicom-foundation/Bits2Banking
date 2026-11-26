<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-cmake.md

PURPOSE:
Give learners an additional practical case for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check two configurations without sharing one build directory

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A course exercise uses a single-configuration CMake generator. It needs separate local Debug and Release settings for the same source.

1. Configure one empty build directory for Debug and read CMAKE_BUILD_TYPE from its cache.
2. Configure a second empty directory for Release. Read its cache and recheck the first directory.

**Check your result.** The first cache contains Debug and the second contains Release. Rechecking the first still shows Debug.

[Step-by-step course guide](../course-guides/learning-cmake.md) · [Full course](../../courses/learning-cmake/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-cmake.md)
