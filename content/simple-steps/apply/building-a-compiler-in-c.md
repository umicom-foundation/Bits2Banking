<!--
Umicom Bits2Banking
File: content/simple-steps/apply/building-a-compiler-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Compiler in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Publish a tiny bytecode inspection note

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice compiler can turn a single constant return into two instructions, PUSH 42 and RETURN.

1. Use Store a program as portable bytes to write the eight UMCB header bytes for two instructions. Name the fields beneath the bytes.
2. Add a two-row instruction listing. Annotate the stack immediately after each instruction and record the result returned.

**Check your result.** The header is 55 4D 43 42 01 00 02 00 in hex. PUSH puts 42 on the stack, and RETURN yields 42.

[Step-by-step course guide](../course-guides/building-a-compiler-in-c.md) · [Full course](../../courses/building-a-compiler-in-c/index.html) · [Small projects by course](index.md) · [First practice case](../practice/building-a-compiler-in-c.md)
