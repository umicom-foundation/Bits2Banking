<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/c23-keyword-reference.md

PURPOSE:
Give learners an additional practical case for C23 Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Explain a counter that resets

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A C23 practice counter uses int visits = 0 inside the function, increments it, and returns it. Two calls both report 1.

1. Mark when visits is initialized in each call. Compare its declaration with the static local example in Control lifetime and access.
2. Change the practice declaration to static int visits = 0 and write each call result on its own line.

**Check your result.** The original sequence is 1, 1. The file-local exercise with a static local reports 1, 2 on the first two calls in a fresh run.

[Step-by-step course guide](../course-guides/c23-keyword-reference.md) · [Full course](../../courses/c23-keyword-reference/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/c23-keyword-reference.md)
