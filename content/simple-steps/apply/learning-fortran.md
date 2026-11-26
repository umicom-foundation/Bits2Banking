<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-fortran.md

PURPOSE:
Give learners an additional practical case for Learning Fortran.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Produce a count report through the C boundary

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local activity report has the independent input counts 6, 250, and 999. It needs the next value for each count.

1. Keep all three inputs in an integer(c_int) array. Use the course interface to call BtbActivityNext on each element.
2. Write each original value beside its result in the report. Check the original array after the loop.

**Check your result.** The report pairs 6 with 7, 250 with 251, and 999 with 1000. The original array still contains 6, 250, and 999.

[Step-by-step course guide](../course-guides/learning-fortran.md) · [Full course](../../courses/learning-fortran/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-fortran.md)
