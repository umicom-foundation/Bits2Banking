<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-spring-framework.md

PURPOSE:
Give learners an additional practical case for Learning Spring Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that an empty service result has a useful response

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch controller formats a list from its supplied room service. The fixture response for no rooms is No rooms available.

1. Use constructor injection to supply a fixture with one room, Gallery. Trace the same route and check its room-list response.
2. Supply a fresh fixture returning no rooms and trace the controller’s empty-data branch with the same route.

**Check your result.** The first case names Gallery once. The second displays No rooms available with no room entries.

[Step-by-step course guide](../course-guides/learning-spring-framework.md) · [Full course](../../courses/learning-spring-framework/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-spring-framework.md)
