<!--
Umicom Bits2Banking
File: content/simple-steps/compare/spring-framework-with-c23.md

PURPOSE:
Give learners an additional practical case for Spring Framework with a Native C23 Receipt Rule.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a wired bean call with a direct native call

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional valid receipt is used as input to both the C test and the Spring bean test.

1. Record the receipt’s fields, units and chosen native status. Mark where the Java provider calls the native function.
2. Use the same input for both traces and compare the result independently of startup messages.

**Check your result.** The direct C and bean requests reach the same native decision under the same input contract.

[Step-by-step course guide](../course-guides/spring-framework-with-c23.md) · [Full course](../../courses/spring-framework-with-c23/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/spring-framework-with-c23.md)
