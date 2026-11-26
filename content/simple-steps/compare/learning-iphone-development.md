<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-iphone-development.md

PURPOSE:
Give learners an additional practical case for Learning iPhone Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the C declaration and implementation

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Swift client calls a C symbol named venue_count. Its bridging header declares the function and a companion C file defines a body returning 7.

1. Place the bridging header and C source on separate lines. Use the connecting-declarations lesson to label when each is needed.
2. Trace an Xcode build with the header visible in both cases. Include the C file in the target only in the second case.

**Check your result.** Both cases have a declaration. The first lacks a linked definition for venue_count. The second links the definition and the call can return 7.

[Step-by-step course guide](../course-guides/learning-iphone-development.md) · [Full course](../../courses/learning-iphone-development/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-iphone-development.md)
