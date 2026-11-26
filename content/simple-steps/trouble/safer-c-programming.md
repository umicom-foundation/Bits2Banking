<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/safer-c-programming.md

PURPOSE:
Give learners an additional practical case for Safer C Programming.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the first out-of-bounds byte

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice writer allocates four bytes for the text `data` and its zero terminator.

1. Write the byte positions for the four characters and the terminator. Mark how many bytes the writer actually owns.
2. Adjust the local buffer to five bytes. Repeat the trace and check whether the representation fits.

**Check your result.** The original terminator needs a fifth byte. Five bytes represent `data` and its terminator.

[Step-by-step course guide](../course-guides/safer-c-programming.md) · [Full course](../../courses/safer-c-programming/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/safer-c-programming.md)
