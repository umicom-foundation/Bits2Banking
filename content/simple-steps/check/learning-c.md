<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-c.md

PURPOSE:
Give learners an additional practical case for Learning C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check process status alongside console output

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local C exercise has a success fixture that prints Saved and a failure fixture that prints Could not save. They end with EXIT_SUCCESS and EXIT_FAILURE respectively.

1. Run the success fixture and read the console line and the shell's process status.
2. Run the failure fixture with the same shell and capture both observations again.

**Check your result.** The first line is Saved with status zero. The second line is Could not save with a nonzero status.

[Step-by-step course guide](../course-guides/learning-c.md) · [Full course](../../courses/learning-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-c.md)
