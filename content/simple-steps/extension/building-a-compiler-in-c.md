<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-a-compiler-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Turn a source expression into a stack trace

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The supported return expression is return 12 - 3 * 2; inside the course's small int main wrapper.

1. Write the seven tokens from return through the semicolon. Draw multiplication under the right-hand side of subtraction.
2. Trace PUSH 12, PUSH 3, PUSH 2, MULTIPLY, SUBTRACT and RETURN. Show the stack after each arithmetic instruction.

**Check your result.** The tokens are return, 12, minus, 3, star, 2 and semicolon. After multiplication the stack has 12 and 6. The return value is 6.

[Step-by-step course guide](../course-guides/building-a-compiler-in-c.md) · [Full course](../../courses/building-a-compiler-in-c/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-a-compiler-in-c.md)
