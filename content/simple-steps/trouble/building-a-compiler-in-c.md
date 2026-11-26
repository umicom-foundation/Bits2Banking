<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/building-a-compiler-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Catch a stack operation with a missing operand

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper CVM program contains PUSH 9, SUBTRACT, RETURN. Its author predicts a result of 9.

1. Use the stack table in Execute instructions with checked arithmetic. Draw the stack after PUSH 9.
2. Count the operands SUBTRACT needs. Mark the instruction where validation must stop.

**Check your result.** The stack holds one value at SUBTRACT. Validation rejects the sequence before execution and produces zero returned arithmetic results.

[Step-by-step course guide](../course-guides/building-a-compiler-in-c.md) · [Full course](../../courses/building-a-compiler-in-c/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/building-a-compiler-in-c.md)
