<!--
Umicom Bits2Banking
File: content/simple-steps/check/fpml-for-treasury.md

PURPOSE:
Give learners an additional practical case for FpML for Treasury and Trade Confirmation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a trade reference's business meaning

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two practice imports use reference M18, already admitted for USD 40,000. One repeats every normalized term. The other changes only its notional to USD 45,000.

1. Apply the ordered import-boundary checklist. Treat both documents as structurally valid at the chosen version.
2. Compare the normalized terms to the stored reference. Require the accepted representation to remain available after both attempts.

**Check your result.** The identical repeat resolves to M18's existing terms. The changed notional is marked a reference conflict and the stored notional remains USD 40,000.

[Step-by-step course guide](../course-guides/fpml-for-treasury.md) · [Full course](../../courses/fpml-for-treasury/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/fpml-for-treasury.md)
