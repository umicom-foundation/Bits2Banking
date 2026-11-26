<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-cmake.md

PURPOSE:
Give learners an additional practical case for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Expose only the header directory consumers need

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A training library has public headers in include and internal headers in src. Its executable consumer uses a public header.

1. Use target_include_directories to give the library a PUBLIC include directory and a PRIVATE src directory.
2. Build the course consumer with its dependency on the library, then examine the generated consumer compile command.

**Check your result.** The consumer builds with the public include directory supplied through the library. The consumer compile command has no propagated src include directory.

[Step-by-step course guide](../course-guides/learning-cmake.md) · [Full course](../../courses/learning-cmake/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-cmake.md)
