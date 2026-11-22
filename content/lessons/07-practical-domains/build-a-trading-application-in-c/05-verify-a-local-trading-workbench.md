<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-trading-application-in-c/05-verify-a-local-trading-workbench.md

PURPOSE:
Use small reproducible inputs and give each refusal its own expected state.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Verify a local trading workbench

[Course contents](index.md) · [Previous · Separate an order from its events](04-separate-the-event-and-the-order.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/05-verify-a-local-trading-workbench.html)

Use small reproducible inputs and give each refusal its own expected state.

## Start your test sheet

- Initial book: expect fill 2 at price 150 on sequence 11.
- No eligible ask: expect no fill and preserve cash, position and result record.
- Duplicate sequence number in the fixture: expect invalid input.
- Large multiplication: expect a range refusal before any write.

Add a test row for a cancelled remainder after an accepted fill when you implement the event log. Verify both the record of that fill and the remaining quantity. This avoids using a final cash number as the only assertion.

## Choose the next thin client

Use a Studio console to show the synthetic summary or a Framework UI for the same read-only view. Keep the engine result and the display format independent. In a separate TMS exercise, hand over the executed quantities and settlement assumptions to the next workflow. No real trading service is attached.

- [Download the complete C23 training order book](../../../labs/native/trading-book-workshop/trading_book.c)
- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Learn to develop with Umicom Framework](../../../courses/umicom-development/index.html)

## Continue in another course

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [FpML for treasury](../../../courses/fpml-for-treasury/index.html)
- [Financial Instruments Pricing](../../../courses/financial-instruments-pricing/index.html)
- [Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)

[Course contents](index.md) · [Previous · Separate an order from its events](04-separate-the-event-and-the-order.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/05-verify-a-local-trading-workbench.html)
