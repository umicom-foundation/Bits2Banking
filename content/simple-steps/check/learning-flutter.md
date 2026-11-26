<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-flutter.md

PURPOSE:
Give learners an additional practical case for Learning Flutter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check byte length with two valid labels

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Dart bridge sends a label’s UTF-8 bytes and their length to a counting fixture in C. Test Cafe and Café with a precomposed é.

1. Use the encoded-bytes lesson to write the expected number of bytes for each label. Keep the displayed letter count in a separate column.
2. Trace each pair through the bridge. Treat the check as passed only when C receives the exact encoded length for both labels.

**Check your result.** Both labels have four displayed letters. C receives four bytes for Cafe and five bytes for Café.

[Step-by-step course guide](../course-guides/learning-flutter.md) · [Full course](../../courses/learning-flutter/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-flutter.md)
