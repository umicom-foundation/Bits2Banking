<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/pricing-from-cashflows/01-build-a-cashflow-timeline.md

PURPOSE:
Read a dated cash flow, distinguish present and future value, and calculate a one-period discount.

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

# Put payments on a timeline and discount them

[Course contents](index.md) · [Previous course — Bookkeeping from Your First Entry](../bookkeeping-from-first-entry/index.md) · [Next lesson — Put a price on a bond's dated promises](02-price-a-fixed-rate-bond.md)

## What you will learn

Read a dated cash flow, distinguish present and future value, and calculate a one-period discount.

## Name the date and amount

A **cash flow** is money paid or received on a date. Put today at time zero. A positive amount means a receipt from the viewpoint named in the exercise. A negative amount means a payment. A **rate** expresses the change per period. Use a consistent currency and time unit throughout.

Suppose a hypothetical account pays a fixed 5% once per year. Under this simple model, $100 today grows to $105 at the end of one year. We assume the payment and rate for the whole period.

## Work it through

1. Convert 5% to 0.05. The multiplier for one year is 1 + 0.05 = 1.05. The 1 keeps the original amount.
2. Multiply $100 by 1.05 to get $105 in one year. That is the **future value** under these assumptions.
3. Reverse the calculation by dividing $105 by 1.05. The **present value** in this model is $100. This reverse process is called **discounting**.
4. For two whole years at the same rate, divide by 1.05 twice, once for each year. Writing 1.05² is a short way to show both multiplications.

## Try it and check

At an annual rate of 10%, what amount today would grow to $121 in two years? Draw the three dates including today.

**Check:** $121 ÷ 1.10 ÷ 1.10 = $100. Multiplying twice returns $121. If you divided once, check how many year-long moves you drew.

## Apply it to an Umicom project

Plan a synthetic Umicom TMS cash-flow preview around amount, currency, valuation date and payment date. Start with this single payment. Show whole-year periods and the assumed annual rate separately. This exercise uses fixed inputs and makes no claim about a live instrument or application result.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/pricing-from-cashflows/lessons/01-build-a-cashflow-timeline.html)

[Course contents](index.md) · [Previous course — Bookkeeping from Your First Entry](../bookkeeping-from-first-entry/index.md) · [Next lesson — Put a price on a bond's dated promises](02-price-a-fixed-rate-bond.md)
