<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-zig.md

PURPOSE:
Give learners an additional practical case for Learning Zig.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find why a failed read appears to succeed

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The course’s local result variable still holds 31 from a prior success. A new call returns an error.

1. Trace the branch that handles the new call. Mark any line that publishes the previous variable as if it were a new result.
2. Place the output use under the accepted branch in a practice copy. Repeat the refused case.

**Check your result.** The refused input retains an explicit error. No new successful result is produced from the old value.

[Step-by-step course guide](../course-guides/learning-zig.md) · [Full course](../../courses/learning-zig/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-zig.md)
