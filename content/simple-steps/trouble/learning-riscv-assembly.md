<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-riscv-assembly.md

PURPOSE:
Give learners an additional practical case for Learning RISC-V Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Save the caller’s return address

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper trace shows a function calling a helper after receiving return address 0x120. The helper call sets ra to 0x180.

1. Compare the routine with the leaf function lesson. Mark why its own helper call changes the return-address register.
2. Trace saving ra before the nested call and restoring it before the outer return.

**Check your result.** ra is 0x180 for the helper’s return. The outer routine restores ra to 0x120 before returning to its caller.

[Step-by-step course guide](../course-guides/learning-riscv-assembly.md) · [Full course](../../courses/learning-riscv-assembly/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-riscv-assembly.md)
