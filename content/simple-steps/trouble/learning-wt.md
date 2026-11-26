<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-wt.md

PURPOSE:
Give learners an additional practical case for Learning Wt.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find application state shared between sessions

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice Wt diagram has sessions A and B starting at an empty filter. One global string supplies both filter displays.

1. Trace session A choosing Kitchen. Mark which value session B would read through the same global string.
2. Move the filter to each session’s application state in the diagram, then repeat the event while B stays idle.

**Check your result.** A displays Kitchen. B still displays its empty filter after the corrected session trace.

[Step-by-step course guide](../course-guides/learning-wt.md) · [Full course](../../courses/learning-wt/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-wt.md)
