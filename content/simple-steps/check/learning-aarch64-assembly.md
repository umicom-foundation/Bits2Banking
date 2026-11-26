<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-aarch64-assembly.md

PURPOSE:
Give learners an additional practical case for Learning AArch64 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check the recorded return address across two call patterns

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper AArch64 trace uses return labels CallerBack and InnerBack. The first function is a leaf. The second saves its caller's link register before making an inner call.

1. Trace the leaf returning through its unchanged link register.
2. Trace the nested call returning to InnerBack, then restore the saved link register and trace the outer return.

**Check your result.** The leaf returns to CallerBack. The nested trace uses InnerBack for the inner return and CallerBack for the final return.

[Step-by-step course guide](../course-guides/learning-aarch64-assembly.md) · [Full course](../../courses/learning-aarch64-assembly/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-aarch64-assembly.md)
