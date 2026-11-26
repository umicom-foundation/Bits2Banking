<!--
Umicom Bits2Banking
File: content/simple-steps/practice/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the first actionable build failure

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A mock configuration result succeeds. The build then reports a missing source file, followed by a stopped build message.

1. Separate configure, compile and link into rows. Put each observed message beside its phase.
2. Write one change that addresses the missing file. Rerun the failed phase before using its output.

**Check your result.** The first compile diagnostic points to the source path. The final stopped message only records the result of that failure.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Practice by course](index.md)
