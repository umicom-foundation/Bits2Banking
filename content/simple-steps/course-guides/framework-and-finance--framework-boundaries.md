<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/framework-and-finance--framework-boundaries.md

PURPOSE:
Provide practical first steps and a result to check for Introduction to Umicom Framework Architecture.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduction to Umicom Framework Architecture

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw two screens that ask for an account balance. Give both arrows the same balance service as their destination. [One service, several applications](../../lessons/06-umicom/framework-studies/framework-boundaries/shared-services.md)
2. Follow the returned value from the service back to each screen. Mark which part owns the account data. [One service, several applications](../../lessons/06-umicom/framework-studies/framework-boundaries/shared-services.md)
3. Trace creation of the learning-pack handle from JSON. Add a line showing when the caller releases the handle. [C interfaces and ownership across languages](../../lessons/06-umicom/framework-studies/framework-boundaries/native-boundaries.md)

**Check your result.** Your drawing shows one balance service and two screens. The handle has one clear release point.

[Continue in the full course](../../courses/framework-and-finance/framework-boundaries/index.html) · [All course guides](index.md)
