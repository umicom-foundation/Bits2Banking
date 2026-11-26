<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-riscv-assembly.md

PURPOSE:
Provide practical first steps and a result to check for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning RISC-V Assembly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Open `add_riscv64.S`. Start a register table with `a0 = 7` and `a1 = 5`. [Trace a leaf function](../../courses/learning-riscv-assembly/lessons/04-trace-a-leaf-function.html)
2. Trace `addw` and `ret`. Repeat on paper with 20 and 3 and record the result register. [Trace a leaf function](../../courses/learning-riscv-assembly/lessons/04-trace-a-leaf-function.html)
3. Take the 32-bit result pattern `80000000` and write its 64-bit sign-extended form. [Trace a leaf function](../../courses/learning-riscv-assembly/lessons/04-trace-a-leaf-function.html)

**Check your result.** The result register `a0` holds 12 and 23 in the first two traces. The final pattern is `FFFFFFFF80000000`.

[Continue in the full course](../../courses/learning-riscv-assembly/index.html) · [All course guides](index.md)
