<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/16-respect-represented-fill-quantities.md

PURPOSE:
Respect small quantities and represented arithmetic

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Respect small quantities and represented arithmetic

## A tolerance has units

A fixed allowance such as one billionth may appear small for a large order, yet exceed an entire tiny order. Adding that allowance to the requested quantity can accept an overfill. Adding it to the filled quantity can mark an incomplete request as complete. The fill owner now uses the actual represented remaining quantity.

The tiny scenario requests 2 to the power minus forty and fills half. Both values are exact powers of two in the binary representation used by the example. This choice isolates the lifecycle boundary from decimal conversion. It is an engineering fixture, not a suggestion that every venue accepts arbitrary fractional quantities.

## Read a hexadecimal floating literal

~~~c
const double requested = 0x1p-40;
report.fill_quantity = requested / 2.0;
/* A partial fill must leave a represented remainder. */
~~~

The p exponent is a power of two. Ordinary decimal literals can require rounding when stored as binary floating-point values. Framework checks finite values, the represented remainder, the proposed total and whether a positive increment actually changes stored quantity. If the increment is lost, accepting its price or profit effect would create inconsistent economics.

## Separate two refusal causes

| Condition | Reason to refuse |
| --- | --- |
| Report exceeds the represented remainder | It would overfill the order |
| Positive addition leaves stored quantity unchanged | The representation cannot express progress |
| Position arithmetic becomes nonfinite | The result is not a usable finite position |
| Quantity is zero or negative | It is not a valid positive fill report |

## Exercise and answer

Would rounding a tiny position to zero for display authorize closing the order? No. Presentation rounding must not alter canonical quantities or lifecycle decisions. Keep display formatting separate from the shared arithmetic. For discrete venue lots, inspect the existing integer-lot APIs instead of inventing another universal epsilon.

## Qualification

The overfill and tiny laboratory scenarios illustrate different boundaries. Broader Framework regression cases also cover subnormal values, adjacent represented values and increments lost beside large quantities. They remain unexecuted until the owner runs them.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/16-respect-represented-fill-quantities.html)
