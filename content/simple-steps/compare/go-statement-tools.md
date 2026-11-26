<!--
Umicom Bits2Banking
File: content/simple-steps/compare/go-statement-tools.md

PURPOSE:
Give learners an additional practical case for Go Statement Tools.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a named-column reader with a fixed-position reader

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local CSV fixture moves the amount column from position two to position three. The fixture's header is id,status,amount and its data row is C1,posted,450.

1. Read the second field by its old position and record what is found.
2. Look up the amount header and read the field at its new position.

**Check your result.** The old position yields posted. The amount header selects 450.

[Step-by-step course guide](../course-guides/go-statement-tools.md) · [Full course](../../courses/go-statement-tools/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/go-statement-tools.md)
