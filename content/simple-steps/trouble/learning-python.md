<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-python.md

PURPOSE:
Give learners an additional practical case for Learning Python.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep a saved list after a malformed read

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice note list contains IDs 3 and 4. A separate input file has an unfinished JSON array.

1. Find the JSON decoding boundary in the course’s save and load exercise. Predict how the incomplete file is reported.
2. Keep the accepted list until a complete new value is decoded and validated. Trace the refused load with the stated IDs.

**Check your result.** The incomplete input yields a decode error. The accepted list still contains 3 and 4 in order.

[Step-by-step course guide](../course-guides/learning-python.md) · [Full course](../../courses/learning-python/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-python.md)
