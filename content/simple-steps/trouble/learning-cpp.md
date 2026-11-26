<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-cpp.md

PURPOSE:
Give learners an additional practical case for Learning C++.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Surface a file-open failure before writing

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A note journal is given a path inside a missing directory in the local exercise.

1. Check the output stream immediately after trying to open the path.
2. Return a failure to the caller and check whether any note was counted as saved.

**Check your result.** The caller gets a file-open failure and the number of saved notes remains zero.

[Step-by-step course guide](../course-guides/learning-cpp.md) · [Full course](../../courses/learning-cpp/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-cpp.md)
