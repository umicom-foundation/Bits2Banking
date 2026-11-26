<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/framework-and-finance.md

PURPOSE:
Provide practical first steps and a result to check for Learning Umicom Framework and Financial Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning Umicom Framework and Financial Systems

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Start on the software route. Draw Bank, TMS and a shared Balances service as three boxes. [One service, several applications](../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html)
2. Draw one read request from each application to Balances. Mark where each application receives the result. [One service, several applications](../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html)
3. Send a fictional transfer through the same service on your diagram. Trace the insufficient-funds response back to the requester. [One service, several applications](../../courses/framework-and-finance/framework-boundaries/lessons/shared-services.html)

**Check your result.** Both read requests reach one balance calculator. The declined transfer leaves the displayed balance unchanged.

[Continue in the full course](../../courses/framework-and-finance/index.html) · [All course guides](index.md)
