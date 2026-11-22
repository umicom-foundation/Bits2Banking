<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-trading-application-in-c/01-turn-an-order-into-a-record.md

PURPOSE:
Distinguish an instruction to trade from a recorded execution.

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

# Turn an order into a record

[Course contents](index.md) · [Next · Find an eligible offer by price and order](02-find-an-eligible-price.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/01-turn-an-order-into-a-record.html)

Distinguish an instruction to trade from a recorded execution.

## Meet a limit and an ask

A buy limit fixes the highest unit price the buyer will accept. A sell offer in our practice book is an ask. A fill records units actually traded. Begin with this fictional sample.

```text
Accept order A71 to buy up to 3 units with a limit of 155 cents per unit
Offer sequence 11 sells 2 units at 150 cents
Offer sequence 12 sells 4 units at 150 cents
Offer sequence 13 sells 3 units at 160 cents
```

## Trace the states

- The request is accepted into the tiny lesson workflow.
- A fill of two units leaves one requested unit unfilled.
- An accepted cancellation of a remaining unit ends that remainder. The earlier fill stays recorded.

A cancel request can still be pending while another event arrives. Keep the latest order state and the reason for an event distinguishable. The FIX Trading Community reference makes this distinction in its order-state model. The exercise uses fictional state labels.

- [FIX Trading Community order-state examples](https://www.fixtrading.org/wp-content/uploads/download-manager-files/FIX-Latest-as-of-EP284-Order-State-Changes.pdf)

## Continue in another course

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [FpML for treasury](../../../courses/fpml-for-treasury/index.html)
- [Financial Instruments Pricing](../../../courses/financial-instruments-pricing/index.html)
- [Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)

[Course contents](index.md) · [Next · Find an eligible offer by price and order](02-find-an-eligible-price.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/01-turn-an-order-into-a-record.html)
