<!--
Umicom Bits2Banking
File: content/simple-steps/extension/framework-and-finance--builds-and-diagnostics.md

PURPOSE:
Give learners an additional practical case for Learning Build and Runtime Diagnostics.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow one missing function from recipe to link

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local practice executable calls read_marker supplied by marker.c. The build compiles main.c and marker.c, then sends only main.o to the link.

1. Use Read each stage of a build to mark which source files compiled and which object defines read_marker.
2. Draft the corrected link inputs for that executable. Keep the new build result separate from the proposed fix.

**Check your result.** The missing input is marker.o. The revised plan links main.o and marker.o. A fresh link result is needed to verify it.

[Step-by-step course guide](../course-guides/framework-and-finance--builds-and-diagnostics.md) · [Full course](../../courses/framework-and-finance/builds-and-diagnostics/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/framework-and-finance--builds-and-diagnostics.md)
