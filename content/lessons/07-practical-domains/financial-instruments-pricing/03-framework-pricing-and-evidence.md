# Framework pricing and comparison evidence

[Course contents](index.md) · [Previous: One price in C, C++ and Java](02-one-price-three-languages.md)

## From a calculation to a reusable service

A successful sample calculation is only a beginning. Different applications need the same convention, validation and error handling. Framework owns that reusable behaviour. Bank, Trader and TMS supply contracts and display results; they should not each invent their own discount formula.

Open the related source file and find umi_quant_discount_curve_present_value. Read its public header under include/umicom/finance/quant/discount_curve.h. A public header declares what callers can request. The implementation shows how the request is handled.

```text
application: amount, rate, days
              |
              v
Framework present-value function
              |
              v
Framework discount-factor function
              |
              v
status + result -> application display and evidence
```

The present-value function takes an output pointer. That means the caller owns a location in memory into which a successful result is written. It returns a status separately. Read the status before using the output; do not use a previous value when a new request fails.

## Build a comparison sheet

1. Record amount 1050, rate 0.05, days 365 and the continuous-compounding convention.
2. Record the C, C++ and Java results from the preceding lesson with more than two decimal places if comparing arithmetic.
3. Record the Framework revision, input values and result when you later run a Framework consumer.
4. Compare with a declared tolerance, for example absolute difference below 0.000001 for this small example. This tolerance is an exercise choice, not a general financial precision policy.
5. Investigate disagreements in assumptions before changing a formula.

A double is an approximate number. Exact equality between independent floating-point implementations is often an unsuitable comparison. For accounting, exact minor units or decimal arithmetic and a stated rounding rule are separate requirements. Also inspect extreme inputs: exp can overflow even when its input is finite. Callers and service contracts must agree how a non-finite output is reported; do not infer safety merely from an input check.

## Exercise

Prepare a test table without running code: zero time; zero rate; negative days; missing output pointer; a very negative finite rate; and a positive rate with a negative cashflow. Which cases are business choices and which are invalid inputs?

## Explained answer

Zero time and zero rate preserve the amount. The inspected Framework routine rejects negative days and a null output pointer. A negative cashflow can represent a payment and is not inherently invalid. Negative rates can be meaningful, but sufficiently extreme inputs can produce overflow: record this boundary as a required numerical check. Never change a failing reference value simply to make all languages agree.

## Where this course goes next

Before coupon bonds, add a schedule of dated payments. Before options, learn payoffs and uncertainty. Before calibration, learn how a model's parameters are fitted to observations. Each step changes the questions the software must answer; none is supplied automatically by one exponential formula.

## Continue learning

[Course contents](index.md) · [Previous: One price in C, C++ and Java](02-one-price-three-languages.md)

[Browser edition](../../../courses/financial-instruments-pricing/lessons/03-framework-pricing-and-evidence.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/src/finance/quant/discount_curve.c). This public revision matches the source inspected for this lesson.
