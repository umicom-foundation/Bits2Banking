<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/framework-and-finance--studio-workflows.md

PURPOSE:
Give learners an additional practical case for Learning Studio Documents and Visual Design.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a missing symbol to its definition

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A report program compiles its main file, but the link step reports an undefined reference to report_total.

1. Find the declaration and the source file that defines report_total in the practice project.
2. Check whether that source file contributes an object to the executable. Add it to the link inputs and rebuild.

**Check your result.** The reference resolves, the executable links, and the practice input prints a total of 12.

[Step-by-step course guide](../course-guides/framework-and-finance--studio-workflows.md) · [Full course](../../courses/framework-and-finance/studio-workflows/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/framework-and-finance--studio-workflows.md)
