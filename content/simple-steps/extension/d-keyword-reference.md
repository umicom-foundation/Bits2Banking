<!--
Umicom Bits2Banking
File: content/simple-steps/extension/d-keyword-reference.md

PURPOSE:
Give learners an additional practical case for D Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Return a reset value with an out parameter

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A D entry starts with 125 cents. You want to test the reset(out int cents) fragment on this variable.

1. Write before and after rows for the caller's cents variable. Follow the out parameter initialization as the call begins.
2. Run or trace reset(cents). Read the caller's value after the function finishes.

**Check your result.** The caller has 125 before the call. The out parameter starts at its int default of 0 and the caller holds 0 afterwards.

[Step-by-step course guide](../course-guides/d-keyword-reference.md) · [Full course](../../courses/d-keyword-reference/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/d-keyword-reference.md)
