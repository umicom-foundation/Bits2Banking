<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-spring-framework.md

PURPOSE:
Give learners an additional practical case for Learning Spring Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare two controller packages for discovery

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch Spring Boot application uses default component discovery from org.example.venue. Two possible locations for a controller are org.example.venue.report and org.example.report.

1. Use the request lesson to locate the application’s base package. Draw the package tree and place both proposed controller locations on it.
2. Apply default discovery without adding any extra configuration. Record whether each location is under the application’s package.

**Check your result.** org.example.venue.report is in the default discovery tree. org.example.report is outside that tree.

[Step-by-step course guide](../course-guides/learning-spring-framework.md) · [Full course](../../courses/learning-spring-framework/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-spring-framework.md)
