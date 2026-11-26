<!--
Umicom Bits2Banking
File: content/simple-steps/check/framework-and-finance--framework-boundaries.md

PURPOSE:
Give learners an additional practical case for Introduction to Umicom Framework Architecture.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check who releases a result after a transfer

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fake service receives a result from a caller. Its practice contract transfers ownership only on acceptance. The release counter starts at zero for each trial.

1. In the accepted trial, have the service release the result when it finishes. Check the counter owned by each side.
2. In the refused trial, keep ownership with the caller and let the caller release the result.

**Check your result.** The accepted trial records one service release. The refused trial records one caller release. Each trial counts exactly one release in total.

[Step-by-step course guide](../course-guides/framework-and-finance--framework-boundaries.md) · [Full course](../../courses/framework-and-finance/framework-boundaries/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/framework-and-finance--framework-boundaries.md)
