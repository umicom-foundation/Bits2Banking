<!--
Umicom Bits2Banking
File: content/simple-steps/check/framework-and-finance--financial-integration.md

PURPOSE:
Give learners an additional practical case for Learning Financial-System Integration.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check absent amount and explicit zero separately

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An offline import contract requires an amount field during mapping. Case one supplies GBP with explicit amount text 0.00. Case two supplies GBP and omits the amount. The mapping exercise permits zero for a later policy check.

1. Use Translate meaning to write one field row for presence, unit and refusal reason. Parse the explicit value according to the marked minor-unit scale.
2. Trace both cases up to the mapping return. Keep the later payment policy out of this check.

**Check your result.** The first case maps to GBP 0 minor units and may proceed to policy evaluation. The second returns a missing-amount refusal before publishing a canonical value.

[Step-by-step course guide](../course-guides/framework-and-finance--financial-integration.md) · [Full course](../../courses/framework-and-finance/financial-integration/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/framework-and-finance--financial-integration.md)
