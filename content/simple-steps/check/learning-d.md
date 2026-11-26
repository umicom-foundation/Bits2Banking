<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-d.md

PURPOSE:
Give learners an additional practical case for Learning D Language.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a validated transfer calculation at zero and above zero

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A D practice validator accepts allocations above zero before calling a calculation function. Use two isolated fixtures with starting cash of 45 cents.

1. Test an allocation of zero and record the validator result and ending cash.
2. Test an allocation of 12 with the same initial amount and record both observations.

**Check your result.** The zero allocation is refused and leaves 45 cents. The allocation of 12 is accepted and leaves 33 cents.

[Step-by-step course guide](../course-guides/learning-d.md) · [Full course](../../courses/learning-d/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-d.md)
