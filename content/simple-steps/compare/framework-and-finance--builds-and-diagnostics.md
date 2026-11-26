<!--
Umicom Bits2Banking
File: content/simple-steps/compare/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two missing-file reports by phase

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A C build reports that settings.h cannot be opened during compilation. A successfully built executable later reports that it cannot open a user-selected settings.txt.

1. Place each line beside configure, compile, link and runtime in the course diagram.
2. For each observation write the expected next verification and identify which generated artifact can already exist.

**Check your result.** The first is a compile input problem and the affected object is missing from that attempt. The second is a runtime file-access problem and an executable already exists.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/framework-and-finance--builds-and-diagnostics.md)
