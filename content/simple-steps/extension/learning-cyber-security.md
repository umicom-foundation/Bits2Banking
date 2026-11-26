<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-cyber-security.md

PURPOSE:
Give learners an additional practical case for Learning Cyber Security.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test the two sides of a safe input length guard

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local validation test limits a display name to 8 characters. The two fixture names have lengths 8 and 9.

1. Test the validator for both lengths before any attempted save. Start with one existing fixture record.
2. Save only accepted test input and check the two results and the resulting record count.

**Check your result.** The 8-character name is accepted, the 9-character name is refused, and the fixture ends with two records.

[Step-by-step course guide](../course-guides/learning-cyber-security.md) · [Full course](../../courses/learning-cyber-security/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-cyber-security.md)
