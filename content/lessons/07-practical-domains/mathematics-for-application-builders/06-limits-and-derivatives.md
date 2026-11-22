<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/mathematics-for-application-builders/06-limits-and-derivatives.md

PURPOSE:
Understand a limit by shrinking an interval and find the derivative of a simple square rule.

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

# Zoom in on a changing rate

[Course contents](index.md) · [Previous lesson — Make a function and read its graph](05-functions-tables-and-slopes.md) · [Next lesson — Build up a total with integrals](07-add-up-a-changing-rate.md)

## What you will learn

Understand a limit by shrinking an interval and find the derivative of a simple square rule.

## Compare an average with a rate at one moment

An **average rate of change** is change in the result divided by change in the input. A **limit** is the value that a calculation approaches as its input gets close to a point. A **derivative** asks which rate the average approaches as the time interval shrinks toward zero. A rate may fail to approach the same number from both sides.

A workshop uses a toy conveyor that has travelled d(t) = t² metres after t seconds. The power ² means multiply a number by itself. The example models a smooth movement near two seconds.

## Work it through

| Time interval after 2 seconds | Calculation in metres per second | Average rate |
| --- | --- | ---: |
| 1 s | (9 − 4) ÷ 1 | 5 |
| 0.1 s | (4.41 − 4) ÷ 0.1 | 4.1 |
| 0.01 s | (4.0401 − 4) ÷ 0.01 | 4.01 |

For a short interval h, the numerator is (2 + h)² − 4 = 4h + h². Divide by h while h is nonzero to get 4 + h. With h values such as −0.1 and +0.1, the rate approaches 4 metres per second from both directions. The derivative at two seconds is 4 metres per second. At any time t in this model, the same expansion gives the derivative 2 × t.

## Try it and check

Use d(t) = t² at t = 3. Calculate the average rate over the next 0.1 seconds. What instantaneous rate should it approach?

**Check:** (9.61 − 9) ÷ 0.1 = 6.1 metres per second. The limit is 6 metres per second. Keep h nonzero while doing the division.

## Apply it to an Umicom project

A Trader practice worksheet can estimate how a model price changes when a rate changes slightly. Keep the interest-rate step separate from the price change and write both units. Lesson 3 in the [pricing course](../../../courses/pricing-from-cashflows/index.html) applies this idea with fictional bond data.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/mathematics-for-application-builders/lessons/06-limits-and-derivatives.html)

[Course contents](index.md) · [Previous lesson — Make a function and read its graph](05-functions-tables-and-slopes.md) · [Next lesson — Build up a total with integrals](07-add-up-a-changing-rate.md)
