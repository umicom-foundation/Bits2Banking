<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-riscv.md

PURPOSE:
Provide practical first steps and a result to check for Introduction to RISC-V.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduction to RISC-V

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw columns for `a0` through `a3`, plus `a7`. Enter 3, 2, 0 and 0 into the four argument columns. [Registers, memory and instructions](../../courses/learning-riscv/lessons/01-registers-and-memory.html)
2. Trace the register moves in `umicom-kernel/programs/diagnostic/entry.S`. Write the values just before the request. [Registers, memory and instructions](../../courses/learning-riscv/lessons/01-registers-and-memory.html)
3. Look up service 3 and selector 2 in `user_abi.h`. Write the expected result register and value. [Registers, memory and instructions](../../courses/learning-riscv/lessons/01-registers-and-memory.html)

**Check your result.** The request number is 3 in `a7` and its selector is 2 in `a0`. The expected reply in `a0` is 64.

[Continue in the full course](../../courses/learning-riscv/index.html) · [All course guides](index.md)
