<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/fpml-for-treasury/index.md

PURPOSE:
Read the two sides of a fictional interest rate swap, preserve the contract terms at import and check the record in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# FpML for Treasury and Trade Confirmation

Read the two sides of a fictional interest rate swap, preserve the contract terms at import and check the record in C23.

## Before you start

Start on paper with the swap drawing. For the optional native exercise, use a C23 compiler that supports -std=c23 in a private practice directory. The examples use fixed synthetic values and need no treasury platform.

## Lessons

1. [Read the Two Sides of a Swap](01-read-the-two-legs.md) — Follow payer, receiver, currency and rate terms before opening a schema.
2. [Read and Validate the Import Boundary](02-read-the-import-boundary.md) — Trace a versioned XML document to a smaller record a treasury service can review.
3. [Check the Mapped Terms in C23](03-check-terms-in-c.md) — Keep amounts and basis points exact at the native boundary and trace rejects without overwriting the result.

[Open the browser course](../../../courses/fpml-for-treasury/index.html)

## Continue learning

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning XML](../../../courses/learning-xml/index.html)
- [Pricing From Cashflows](../../../courses/pricing-from-cashflows/index.html)
- [Introduction to Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)
- [Build a trading application in C](../../../courses/build-a-trading-application-in-c/index.html)
- [Swift Payment Messages and ISO 20022](../../../courses/swift-payment-messages/index.html)

