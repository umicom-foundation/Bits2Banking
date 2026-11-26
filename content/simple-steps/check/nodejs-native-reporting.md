<!--
Umicom Bits2Banking
File: content/simple-steps/check/nodejs-native-reporting.md

PURPOSE:
Give learners an additional practical case for Node.js and Native Statement Reports.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a binding with and without its required field

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use a valid local report carrying 500 cents and a second object with its amount omitted.

1. Write the accepted shape and expected refusal before using the course’s JS validator.
2. Compare both outcomes and inspect whether a static display reports a result for the incomplete object.

**Check your result.** The first object is accepted with 500 cents. The missing-amount object is refused before it supplies a complete display result.

[Step-by-step course guide](../course-guides/nodejs-native-reporting.md) · [Full course](../../courses/nodejs-native-reporting/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/nodejs-native-reporting.md)
