<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-cmake.md

PURPOSE:
Give learners an additional practical case for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a report tool with a separate reusable target

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice CMake project has helper.c for a function that adds two counts and main.c for a console executable that calls the helper with 2 and 5.

1. Create a library target from helper.c and an executable target from main.c, then add the target dependency through target_link_libraries.
2. Configure and build in an empty practice build directory with the course commands. Run the console target.

**Check your result.** Both named targets build. The console prints the helper result of 7.

[Step-by-step course guide](../course-guides/learning-cmake.md) · [Full course](../../courses/learning-cmake/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-cmake.md)
