<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/pricing-from-cashflows/02-price-a-fixed-rate-bond.md

PURPOSE:
List each coupon and face-value payment, discount the payments, and compare the results at two rates.

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

# Put a price on a bond's dated promises

[Course contents](index.md) · [Previous lesson — Put payments on a timeline and discount them](01-build-a-cashflow-timeline.md) · [Next lesson — Measure a bond price's rate sensitivity](03-measure-an-interest-rate-shift.md)

## What you will learn

List each coupon and face-value payment, discount the payments, and compare the results at two rates.

## Read the contract vocabulary

A **bond** is a contract that sets out payments by a borrower to the holder. The **face value** is the amount repaid at the end under the simple bond used here. A **coupon** is an interest payment. **Maturity** is the date the face value is due.

Our two-year teaching bond has $100 face value and gives one $4 coupon at each year-end. Assume the valuation date is at the start, each payment happens as described, and the same annual discount rate applies to both years.

## Work it through

| Time | What the holder receives | Amount |
| --- | --- | ---: |
| Year 1 | First coupon | $4 |
| Year 2 | Second coupon plus face value | $104 |

1. At a 5% annual discount rate, year one is $4 ÷ 1.05, or about $3.81.
2. Year two is $104 ÷ (1.05 × 1.05), or about $94.33.
3. Add the unrounded values, then round the final result for display. The model price is about $98.14.
4. Set the rate to 4%. The price is $100 in this example. At the higher 5% rate, the same future payments had a lower present value.

~~~text
SET running price to zero
FOR each payment in date order
    ADD payment amount divided by its discount multiplier
SHOW price rounded for display
~~~

This is **pseudocode**. It describes a routine in readable steps and gives you something to check before using a programming language.

## Try it and check

Replace the coupons with $3 and keep the rate at 5%. What payments do you discount and what is the resulting display value?

**Check:** Discount $3 for one year and $103 for two years. The total is about $96.28. Include the face value once, with the last coupon.

## Apply it to an Umicom project

Use the hand calculation as a test expectation for a sample Framework pricing function called from Umicom Trader. Record the actual cash-flow list and the rate alongside the result. The existing [multi-language pricing course](../../../courses/financial-instruments-pricing/index.html) shows how real Framework services and comparison evidence belong together.

## Optional C practice

When you are ready to run a program, save this as bond.c in a practice folder. This example performs the two-year calculation only. The intermediate amounts stay unrounded until the program displays them.

~~~c
#include <stdio.h>

int main(void)
{
    const double rate = 0.05;
    const double first_multiplier = 1.0 + rate;
    const double second_multiplier = first_multiplier * first_multiplier;
    const double price = 4.0 / first_multiplier + 104.0 / second_multiplier;

    printf("Model price: %.2f\n", price);
    return 0;
}
~~~

If GCC is already available in PowerShell, use these commands.

~~~powershell
gcc -std=c23 -Wall -Wextra bond.c -o bond.exe
.\bond.exe
~~~

Expect `Model price: 98.14`. If your compiler does not recognise the option, check its documented C23 support before continuing. If the executable is missing, read the compiler message and confirm that you saved bond.c in your current directory. Use the paper calculation whenever a compiler is unavailable.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/pricing-from-cashflows/lessons/02-price-a-fixed-rate-bond.html)

[Course contents](index.md) · [Previous lesson — Put payments on a timeline and discount them](01-build-a-cashflow-timeline.md) · [Next lesson — Measure a bond price's rate sensitivity](03-measure-an-interest-rate-shift.md)
