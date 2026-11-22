<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/pricing-from-cashflows/03-measure-an-interest-rate-shift.md

PURPOSE:
Estimate a local price response to a small change in the assumed rate and distinguish a percentage point from a percent.

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

# Measure a bond price's rate sensitivity

[Course contents](index.md) · [Previous lesson — Put a price on a bond's dated promises](02-price-a-fixed-rate-bond.md) · [Next lesson — Distinguish a forward delivery price from its value](04-distinguish-forward-price-and-value.md)

## What you will learn

Estimate a local price response to a small change in the assumed rate and distinguish a percentage point from a percent.

## Name the change and the unit

Price sensitivity describes how much a price changes when an input changes. Use only one model input change at a time. One **basis point** is one hundredth of a percentage point. Moving the annual discount rate from 5.00% to 5.01% is one basis point. In decimal rate units, that step is 0.0001.

## Work it through

Reuse the $4 and $104 cash flows from the previous lesson. Use the unrounded calculation values.

1. At annual rate 0.05, the price is approximately $98.14059.
2. At annual rate 0.0501, the price is approximately $98.12226.
3. Subtract the base price from the shifted price. The change is roughly −$0.0183 per one-basis-point increase. The minus sign tells you in which direction the result moved.
4. The change divided by 0.0001 is about −183 dollars per one decimal unit of rate. The large-looking number is a unit conversion. It describes the slope near 5%, and a shift of one unit is outside the small change used to compute it.

## Try it and check

What discount rate is one basis point below 5%? Should this hypothetical bond’s price rise or fall under that shift?

**Check:** 4.99%, or 0.0499. The price rises under these assumptions because both positive payments are divided by smaller factors. Write the original and shifted rate side by side if you are unsure of the sign.

## Apply it to an Umicom project

Prepare a baseline and a one-basis-point scenario for an Umicom Trader or TMS practice report. Write both the estimated price change and its direction. A future extension can repeat the comparison for increases and decreases and compare the result with the [first derivative lesson](../../../courses/mathematics-for-application-builders/lessons/06-limits-and-derivatives.html).

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/pricing-from-cashflows/lessons/03-measure-an-interest-rate-shift.html)

[Course contents](index.md) · [Previous lesson — Put a price on a bond's dated promises](02-price-a-fixed-rate-bond.md) · [Next lesson — Distinguish a forward delivery price from its value](04-distinguish-forward-price-and-value.md)
