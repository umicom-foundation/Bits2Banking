<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/spring-framework-with-c23.md

PURPOSE:
Give learners an additional practical case for Spring Framework with a Native C23 Receipt Rule.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a unit mismatch across JNI

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice Java client passes 6 in whole currency units. The C rule reads 6 cents.

1. Write the expected interface units on both sides. Trace where the transfer first loses its unit agreement.
2. Make the caller pass the equivalent 600 cents using the course’s documented narrow interface. Compare with a direct C run.

**Check your result.** Both calls now use 600 cents. Their decision can be compared for the same input.

[Step-by-step course guide](../course-guides/spring-framework-with-c23.md) · [Full course](../../courses/spring-framework-with-c23/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/spring-framework-with-c23.md)
