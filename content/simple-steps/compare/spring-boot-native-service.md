<!--
Umicom Bits2Banking
File: content/simple-steps/compare/spring-boot-native-service.md

PURPOSE:
Give learners an additional practical case for Spring Boot with a Native C23 Service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare loading failure and rule refusal

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable service has one configuration with a missing native library and one valid configuration with a refused input.

1. Write the two prerequisites, locating the library and calling its rule. Trace the first observed outcome for each case.
2. Compare whether the native rule was reached, keeping diagnostic source and input in your report.

**Check your result.** The missing library fails earlier at configuration or loading. The valid library can return a refusal from the rule.

[Step-by-step course guide](../course-guides/spring-boot-native-service.md) · [Full course](../../courses/spring-boot-native-service/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/spring-boot-native-service.md)
