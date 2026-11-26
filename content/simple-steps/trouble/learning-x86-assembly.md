<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-x86-assembly.md

PURPOSE:
Give learners an additional practical case for Learning x86 Assembly.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use the caller’s argument registers

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Windows x64 routine reads its two integer arguments from RDI and RSI. The practice call describes 7 in RCX and 9 in RDX.

1. Compare the Windows and System V calling tables in the lesson. Write the two argument locations for the Windows call.
2. Trace the addition using the documented Windows register positions and put the result in the return register.

**Check your result.** The routine reads 7 and 9 from RCX and RDX and returns 16 in RAX.

[Step-by-step course guide](../course-guides/learning-x86-assembly.md) · [Full course](../../courses/learning-x86-assembly/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-x86-assembly.md)
