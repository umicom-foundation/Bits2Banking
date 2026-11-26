<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-nim.md

PURPOSE:
Give learners an additional practical case for Learning Nim.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a Nim binding name and a C linker symbol

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch local Nim call uses the name activityNext. The C object supplies BtbActivityNext.

1. Find the Nim proc name and the importc string from the interoperability lesson. Make one row for the source-language name and one for the C name.
2. Compare a binding retaining importc BtbActivityNext with a scratch declaration selecting an absent external name BtbActivityNew.

**Check your result.** The original resolves BtbActivityNext while retaining the local name activityNext. The alternate declaration looks for a symbol the stated object does not provide.

[Step-by-step course guide](../course-guides/learning-nim.md) · [Full course](../../courses/learning-nim/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-nim.md)
