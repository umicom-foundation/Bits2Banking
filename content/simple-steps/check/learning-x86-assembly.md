<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-x86-assembly.md

PURPOSE:
Give learners an additional practical case for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a return value produced by two instruction sequences

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper x86-64 object-code exercise compares a routine returning zero through xor eax, eax with another returning zero through mov eax, 0.

1. Use the object inspection lesson to identify which instruction produced each zero. Mark the register after that instruction in each case.
2. Record the value observed by the caller after the routine returns and retain both different instruction names in the evidence.

**Check your result.** The two instruction sequences differ and both return integer zero through the return register.

[Step-by-step course guide](../course-guides/learning-x86-assembly.md) · [Full course](../../courses/learning-x86-assembly/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-x86-assembly.md)
