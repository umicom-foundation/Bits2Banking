<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/automated-testing-with-umicom.md

PURPOSE:
Give learners an additional practical case for Automated Testing with Umicom Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate a fixture link failure from a test failure

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Reader links successfully. Its Probe fixture reports an undefined reference to open_tree, and Trees is absent from Probe's build plan.

1. Read the Probe and Trees example in Check the link inputs of a fixture. Mark the library that supplies open_tree.
2. Add Trees to Probe's link list on paper. Record the evidence you would need next for a passing decoder check.

**Check your result.** The observation is a Probe link failure. The next evidence is a successful Probe link and a passing decoder check from that executable.

[Step-by-step course guide](../course-guides/automated-testing-with-umicom.md) · [Full course](../../courses/automated-testing-with-umicom/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/automated-testing-with-umicom.md)
