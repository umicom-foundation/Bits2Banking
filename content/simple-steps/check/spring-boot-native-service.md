<!--
Umicom Bits2Banking
File: content/simple-steps/check/spring-boot-native-service.md

PURPOSE:
Give learners an additional practical case for Spring Boot with a Native C23 Service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check one startup path and one native rejection

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

One local run has the documented library prefix. A second test uses that same valid prefix with an input outside the lab’s accepted set.

1. Mark the startup stages both runs share. Identify where the checked input reaches the native service.
2. Compare the accepted and refused results at the rule boundary, keeping the successful library-load observation separate.

**Check your result.** Both runs reach the native rule. Their result differs according to whether the input is accepted by that rule.

[Step-by-step course guide](../course-guides/spring-boot-native-service.md) · [Full course](../../courses/spring-boot-native-service/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/spring-boot-native-service.md)
