<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-cpp.md

PURPOSE:
Give learners an additional practical case for Learning C++.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check two inputs at a C and C++ boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local integration fixture gives C++ a C helper for converting whole minutes into seconds. It multiplies its nonnegative input by 60 and returns the result without storing state.

1. Through the shared C declaration, call the helper with 3 from the C++ test.
2. Call the same helper with 0 and record the integer result separately.

**Check your result.** The calls return 180 and 0 respectively through the same declaration.

[Step-by-step course guide](../course-guides/learning-cpp.md) · [Full course](../../courses/learning-cpp/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-cpp.md)
