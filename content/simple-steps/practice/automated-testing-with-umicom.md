<!--
Umicom Bits2Banking
File: content/simple-steps/practice/automated-testing-with-umicom.md

PURPOSE:
Give learners an additional practical case for Automated Testing with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Write a check that can fail clearly

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice notes program should save one line and read it back when reopened.

1. Write the setup, action and expected result on separate lines. Use a temporary destination for the practice file.
2. Write a second case for a missing source file. Give the cleanup step its own result.

**Check your result.** The first case expects the exact line. The missing-file case records its refusal even when cleanup succeeds.

[Step-by-step course guide](../course-guides/automated-testing-with-umicom.md) · [Full course](../../courses/automated-testing-with-umicom/index.html) · [Practice by course](index.md)
