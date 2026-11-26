<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-a-compiler-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the lexer at the final comment byte

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One in-memory source span is the seven bytes of /*end*/. Another is its first six bytes, ending after the asterisk.

1. Number each byte from zero. Trace the lexer to the end of the first span and to the unclosed comment in the second.
2. Write the expected end-of-input or diagnostic status and the point where a safe implementation must stop reading.

**Check your result.** The seven-byte span ends successfully with no ordinary tokens. The six-byte span reports UMC_SYNTAX_ERROR at the opening comment position and performs zero reads beyond the span.

[Step-by-step course guide](../course-guides/building-a-compiler-in-c.md) · [Full course](../../courses/building-a-compiler-in-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-a-compiler-in-c.md)
