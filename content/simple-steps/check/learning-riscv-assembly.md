<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-riscv-assembly.md

PURPOSE:
Give learners an additional practical case for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a linker-visible call before and after supplying its definition

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An Assembly object calls a local training routine named room_sum. The first fixture contains the calling object alone. The second also contains one object defining room_sum.

1. Use the unresolved-call lesson to locate the symbol reference in the caller’s object. Set an expected link outcome for the first fixture.
2. Trace the second link with the provided definition and keep the input object record beside the outcome.

**Check your result.** The first fixture leaves room_sum unresolved. The second has one supplied definition for that reference and resolves it.

[Step-by-step course guide](../course-guides/learning-riscv-assembly.md) · [Full course](../../courses/learning-riscv-assembly/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-riscv-assembly.md)
