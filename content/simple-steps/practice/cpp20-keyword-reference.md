<!--
Umicom Bits2Banking
File: content/simple-steps/practice/cpp20-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C++20 Keyword and Token Reference.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow ownership through a short scope

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice object is created inside a block and the block ends after one output line.

1. Find the declaration and the closing brace in the course example. Mark the lifetime of the object on a three-line trace.
2. Move a display statement inside and then outside that lifetime in a practice copy. Record what the compiler says about the name outside.

**Check your result.** The local name is usable inside the block. The compiler reports the out-of-scope use in the separate copy.

[Step-by-step course guide](../course-guides/cpp20-keyword-reference.md) · [Full course](../../courses/cpp20-keyword-reference/index.html) · [Practice by course](index.md)
