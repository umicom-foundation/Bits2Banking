<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-trading-application-in-c/02-find-an-eligible-price.md

PURPOSE:
Use an explicit policy to choose a seller on a paper order book.

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

# Find an eligible offer by price and order

[Course contents](index.md) · [Previous · Turn an order into a record](01-turn-an-order-into-a-record.md) · [Next · Commit cash, position and fill together](03-commit-cash-positions-and-fill.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/02-find-an-eligible-price.html)

Use an explicit policy to choose a seller on a paper order book.

## Choose a deterministic rule

In this lesson, the best ask has the lowest eligible price. Earlier accepted sequence numbers break a tie. The console makes at most one fill per call. Many venues and products use their own matching rules.

```text
FOR EACH available ask
    SKIP if its price exceeds the buyers limit
    CHOOSE if its price is lower than the current best
    AT equal price keep the earlier sequence
END FOR
```

## See the D comparison

```d
bool earlierAsk(long price, ulong seq, long bestPrice, ulong bestSeq)
{
    return price < bestPrice || (price == bestPrice && seq < bestSeq);
}
```

The actual C23 helper also validates each offer’s sequence, price and units before using it. Try moving the row for sequence 12 ahead of 11. At an equal price, 11 remains first. Lowering the limit to 140 yields no eligible ask.

- [Download the complete C23 training order book](../../../labs/native/trading-book-workshop/trading_book.c)

## Continue in another course

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [FpML for treasury](../../../courses/fpml-for-treasury/index.html)
- [Financial Instruments Pricing](../../../courses/financial-instruments-pricing/index.html)
- [Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)

[Course contents](index.md) · [Previous · Turn an order into a record](01-turn-an-order-into-a-record.md) · [Next · Commit cash, position and fill together](03-commit-cash-positions-and-fill.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/02-find-an-eligible-price.html)
