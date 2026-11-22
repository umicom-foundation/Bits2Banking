<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/mathematics-for-application-builders/07-add-up-a-changing-rate.md

PURPOSE:
Use rectangles to approximate how much has accumulated and connect that sum to a definite integral.

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

# Build up a total with integrals

[Course contents](index.md) · [Previous lesson — Zoom in on a changing rate](06-limits-and-derivatives.md) · [Next course — Bookkeeping from Your First Entry](../bookkeeping-from-first-entry/index.md)

## What you will learn

Use rectangles to approximate how much has accumulated and connect that sum to a definite integral.

## What accumulates?

If a pump runs for three minutes at 2 litres per minute, the total is 6 litres. The minutes cancel when you multiply rate by time. When a rate changes, you can use many short intervals, estimate one amount in each, and add the amounts.

A different training pump follows r(t) = 2 × t litres per minute, where t is time in minutes. From t = 0 to t = 3, the graph climbs from zero to 6 litres per minute.

## Work it through

1. Split three minutes into three one-minute pieces. The left edges are t = 0, 1 and 2; their heights are 0, 2 and 4. Multiply each by one minute and add to get 6 litres.
2. Using the right edges instead gives 2 + 4 + 6 = 12 litres. The rate climbs, so the left sum is below the total and the right sum is above it.
3. Shrink each piece to half a minute. The left sum is 7.5 litres and the right sum is 10.5 litres. The gap shrinks.
4. The graph’s exact area is a triangle: one half × 3 minutes × 6 litres per minute = 9 litres. A **definite integral** is the limit of these sums as pieces get fine enough. Here, it is the total over minutes zero through three.

## Try it and check

Use the same pump for only two minutes. Sketch the shape or list the start and end rates. Find the exact amount and a left-edge estimate with two one-minute pieces.

**Check:** The triangle has base 2 and height 4, so its total is 4 litres. The two left-endpoint rectangles add to 0 + 2 = 2 litres. If your result still says litres per minute, include each rectangle’s duration.

## Apply it to an Umicom project

In a Media practice project, calculate a transfer total from a changing rate chart. Add separate measured intervals and label the total in bytes. If a chart fills in unmeasured values, label the estimate. The physical pump example teaches the same rate-to-total idea without requiring an installed app.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/mathematics-for-application-builders/lessons/07-add-up-a-changing-rate.html)

[Course contents](index.md) · [Previous lesson — Zoom in on a changing rate](06-limits-and-derivatives.md) · [Next course — Bookkeeping from Your First Entry](../bookkeeping-from-first-entry/index.md)
