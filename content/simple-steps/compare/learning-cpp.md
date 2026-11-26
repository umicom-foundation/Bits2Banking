<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-cpp.md

PURPOSE:
Give learners an additional practical case for Learning C++.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare an owned snapshot with a const reference

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice vector initially contains 7 and 9. A local reporter has both an owned copy and a const reference to the caller's vector.

1. Add 12 to the caller's vector after taking the copy and reference.
2. Read the element count through each representation without modifying either from the reporter.

**Check your result.** The owned snapshot still contains two elements. The reference sees the caller's three elements.

[Step-by-step course guide](../course-guides/learning-cpp.md) · [Full course](../../courses/learning-cpp/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-cpp.md)
