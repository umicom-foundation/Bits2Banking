<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-trading-application-in-c/04-separate-the-event-and-the-order.md

PURPOSE:
Design an event log that preserves previous fills and makes duplicate events detectable.

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

# Separate an order from its events

[Course contents](index.md) · [Previous · Commit cash, position and fill together](03-commit-cash-positions-and-fill.md) · [Next · Verify a local trading workbench](05-verify-a-local-trading-workbench.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/04-separate-the-event-and-the-order.html)

Design an event log that preserves previous fills and makes duplicate events detectable.

## Use an identity for each purpose

Give the order an order identifier and each observed event its own identifier. A partial execution references its order and event. An accepted cancel references the remainder it closes. Repeating a fill event with its original identifier must not add another cash debit or another position change.

```text
Order A71: buy up to 3 units
Event E201: fill 2 at 150 each; open quantity 1
Duplicate E201: keep the previously recorded result
Event E202: cancel remaining 1; open quantity 0
```

The linked C order book demonstrates one match. An event log, duplicate admission and cancelling the remainder are further design exercises. Store the cause and varying amounts using the same native types you checked earlier.

## Apply it to Trader

Design a practice status line that shows the order, the current open units and the last event. Record the difference between a repeated report and a newly accepted fill. A broker or venue adapter would have its own format and test suite.

- [FIX Business Area Trade](https://archive.fixtrading.org/online-specification/business-area-trade/)
- [Framework trading and post-trade lessons](../../../courses/framework-and-finance/trading-and-posttrade/index.html)

## Continue in another course

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [FpML for treasury](../../../courses/fpml-for-treasury/index.html)
- [Financial Instruments Pricing](../../../courses/financial-instruments-pricing/index.html)
- [Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)

[Course contents](index.md) · [Previous · Commit cash, position and fill together](03-commit-cash-positions-and-fill.md) · [Next · Verify a local trading workbench](05-verify-a-local-trading-workbench.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/04-separate-the-event-and-the-order.html)
