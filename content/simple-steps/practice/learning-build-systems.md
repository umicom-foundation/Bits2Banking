<!--
Umicom Bits2Banking
File: content/simple-steps/practice/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find what needs rebuilding

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Files `report.c` and `view.c` both include `report.h`. A build output uses both objects.

1. Draw an arrow from each input to the object it affects. Draw arrows from the objects to the final program.
2. Mark only `report.h` changed. Identify each result that needs rebuilding in the correct order.

**Check your result.** Both objects need rebuilding before the final link.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Practice by course](index.md)
