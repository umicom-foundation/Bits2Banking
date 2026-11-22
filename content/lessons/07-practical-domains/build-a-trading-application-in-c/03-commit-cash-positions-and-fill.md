<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-trading-application-in-c/03-commit-cash-positions-and-fill.md

PURPOSE:
Check range and available cash before creating a synthetic fill.

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

# Commit cash, position and fill together

[Course contents](index.md) · [Previous · Find an eligible offer by price and order](02-find-an-eligible-price.md) · [Next · Separate an order from its events](04-separate-the-event-and-the-order.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/03-commit-cash-positions-and-fill.html)

Check range and available cash before creating a synthetic fill.

## Trace one fill

The order requests 3 units. The best ask has just 2 available. The chosen fill therefore has 2 units at 150 cents per unit, so its cost is 300 cents. Cash falls from 1,000 to 700 and the position becomes 2 units.

## Check the arithmetic first

The C23 helper chooses the smaller of requested and available units. Before multiplying it compares units with the maximum representable number divided by price. The selected fill is refused if its cost exceeds recorded cash or the new position would exceed its range. The checks finish before the helper changes the book.

- [Download the complete C23 training order book](../../../labs/native/trading-book-workshop/trading_book.c)

In a learning copy, compile with `gcc -std=c23 -Wall -Wextra -Wpedantic trading_book.c -o trading_book`. On Windows use `-o trading_book.exe`. Then run the resulting practice program from that same folder. If compilation fails, read the first diagnostic and confirm you saved an unchanged copy of the source.

```text
Filled 2 at 150 cents on ask 11
Cash: 700 cents; units: 2
```

## Try it

Trace what happens if the starting cash was 299. The chosen 300-cent fill exceeds the cash limit. No state changes. Add this exercise to your local copy along with its distinct expected refusal.

## Continue in another course

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [FpML for treasury](../../../courses/fpml-for-treasury/index.html)
- [Financial Instruments Pricing](../../../courses/financial-instruments-pricing/index.html)
- [Treasury Management Systems](../../../courses/introduction-to-treasury-management-systems/index.html)

[Course contents](index.md) · [Previous · Find an eligible offer by price and order](02-find-an-eligible-price.md) · [Next · Separate an order from its events](04-separate-the-event-and-the-order.md) · [Browser edition](../../../courses/build-a-trading-application-in-c/lessons/03-commit-cash-positions-and-fill.html)
