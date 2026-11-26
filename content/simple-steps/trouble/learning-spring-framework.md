<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-spring-framework.md

PURPOSE:
Give learners an additional practical case for Learning Spring Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find the call that bypassed the supplied service

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice controller has a constructor for its report service. The handler creates another service inside the request method.

1. Trace the handler in the constructor-injection lesson and give the supplied service and the new service different identities on paper.
2. Use the supplied constructor value in the scratch handler. Set its fake report text to Workshop ready and run or trace one local request.

**Check your result.** The response contains Workshop ready and the supplied service receives exactly one request.

[Step-by-step course guide](../course-guides/learning-spring-framework.md) · [Full course](../../courses/learning-spring-framework/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-spring-framework.md)
