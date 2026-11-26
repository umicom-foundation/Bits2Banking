<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/building-a-compiler-in-c.md

PURPOSE:
Provide practical first steps and a result to check for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Building a Compiler in C

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Trace the lesson’s `return 7 * 6;` from source text to the value produced by the running program. [From source text to a result](../../courses/building-a-compiler-in-c/lessons/01-source-and-execution.html)
2. Split `return 12;` into tokens. Compare it with `return12;` and mark the identifier. [Read one token at a time](../../courses/building-a-compiler-in-c/lessons/02-reading-tokens.html)
3. In the original expression, replace the multiply symbol with plus. Predict the result and identify what changes in the instructions. [From source text to a result](../../courses/building-a-compiler-in-c/lessons/01-source-and-execution.html)

**Check your result.** The result changes from 42 to 13. `return12` is one identifier and has no separate `return` token.

[Continue in the full course](../../courses/building-a-compiler-in-c/index.html) · [All course guides](index.md)
