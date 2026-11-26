<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-cmake.md

PURPOSE:
Provide practical first steps and a result to check for Learning CMake.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning CMake

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. From the Bits2Banking checkout with the tools ready, type `cmake -S labs/native/bounded-ledger-line -B build/ledger-line -G Ninja -DBUILD_TESTING=ON`. [Follow source files to a running program](../../lessons/05-engineering/learning-cmake/01-follow-source-to-program.md)
2. Build with `cmake --build build/ledger-line --parallel 2`. Find the generated files in the build folder. [Keep source and build directories separate](../../lessons/05-engineering/learning-cmake/03-separate-source-and-build.md)
3. Run `ctest --test-dir build/ledger-line --output-on-failure --no-tests=error`. [Keep source and build directories separate](../../lessons/05-engineering/learning-cmake/03-separate-source-and-build.md)

**Check your result.** The source and generated outputs are in separate folders. The tests for syntax, mutations and the example all pass.

[Continue in the full course](../../courses/learning-cmake/index.html) · [All course guides](index.md)
