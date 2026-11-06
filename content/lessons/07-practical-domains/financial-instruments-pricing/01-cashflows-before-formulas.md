# Cashflows before formulas

[Course contents](index.md) · [Next: One price in C, C++ and Java](02-one-price-three-languages.md)

## Begin with the agreement

An instrument is a financial agreement. A deposit promises a later payment; a bond may promise several payments. Pricing estimates a value today under stated assumptions. It does not establish that the payer will pay, nor recommend buying the instrument.

No programming is needed for this lesson. Use addition, multiplication and a calculator. A cashflow is an amount attached to a date and currency. From the holder's point of view, money received is positive; money paid is negative. Choosing the other party's viewpoint reverses the signs.

Suppose a practice contract pays 1,050 currency units in exactly one year. A hypothetical alternative grows money by 5% in that year. How much money today would grow to the same amount? Write the relationship first:

```text
today: P                         one year later: 1,050
   |----------- grow by 1.05 ------------>|
P * 1.05 = 1,050
P = 1,050 / 1.05 = 1,000
```

Here P is the present value. The discount factor is 1 / 1.05. Multiplying a future cashflow by that factor moves its value to today. A rate of 5% is written 0.05 in calculations: divide a percentage by 100. Using 5 instead of 0.05 means 500%, a different input.

## Describe the inputs

1. Write the currency, payment amount and payment date.
2. Write the valuation date: the date on which value is measured.
3. State the rate convention. This example uses one annual growth period.
4. Record whether default, fees, tax and currency conversion are included. Here they are omitted.
5. Keep the input record with the result. A number without its assumptions cannot be reproduced.

Two currency amounts cannot be added just because both are numbers. Nor is a displayed bank balance the same thing as an estimated present value. A settlement ledger typically records precise currency units; an analytical pricing calculation may use approximate floating-point numbers.

## Exercise

A contract pays 525 after one year. Use the same 5% annual convention. Find its present value, then explain what happens when the discount rate rises to 10% while the payment stays unchanged.

## Explained answer

525 / 1.05 = 500. At 10%, 525 / 1.10 is approximately 477.27. The denominator increases, so the present value decreases. This conclusion assumes a fixed positive future payment; it is not a universal claim about every financial product.

## Connect to Umicom

The linked Framework file separates discount-factor calculation from multiplying the future amount. Its convention is continuous compounding with days divided by 365, which is different from this first annual example. The next lesson explains that difference before using the API.

## Continue learning

[Course contents](index.md) · [Next: One price in C, C++ and Java](02-one-price-three-languages.md)

[Browser edition](../../../courses/financial-instruments-pricing/lessons/01-cashflows-before-formulas.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/src/finance/quant/discount_curve.c). This public revision matches the source inspected for this lesson.
