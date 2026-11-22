<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/pricing-from-cashflows/05-price-a-one-step-option.md

PURPOSE:
Calculate a call payoff in each outcome and discount the weighted result in a one-step model.

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

# Price a call option in a two-outcome model

[Course contents](index.md) · [Previous lesson — Distinguish a forward delivery price from its value](04-distinguish-forward-price-and-value.md) · [Continue with Financial Instruments Pricing Using C, C++ and Java](../../../courses/financial-instruments-pricing/index.html)

## What you will learn

Calculate a call payoff in each outcome and discount the weighted result in a one-step model.

## Read the right to buy

A **call option** gives the holder a right to buy at an agreed **strike price**. In this exercise the holder may exercise at the end of the period. The payoff then is the larger of zero and final item price minus strike. The **price** is the amount paid now for the option, which is a separate number from either future payoff.

Assume today's asset price is $100. At the end of one period it is either $120 or $90, and the risk-free period multiplier is 1.02. The call strike is $105. Ignore costs and other market frictions. This is a simplified model for learning.

## Work it through

1. In the up outcome, the call pays 120 − 105 = $15. In the down outcome, its payoff is zero.
2. A **risk-neutral weight** is the up-outcome weight that makes the asset price in the model grow to $102 before discounting. It is a pricing input derived from these assumptions. It does not forecast which outcome will happen.
3. Find the up weight by solving 120 × p + 90 × (1 − p) = 102. This reduces to 30 × p = 12, so p = 0.4. The down weight is 0.6.
4. Weight the payoffs and discount the total: (0.4 × 15 + 0.6 × 0) ÷ 1.02 = about $5.88 today.

Check model inputs first. If the risk-free growth result lies outside the up/down range or on its endpoints, this exercise's strictly positive weights cannot be constructed.

## Try it and check

Keep the same asset model and change the strike to $115. What are the two payoffs and the model price?

**Check:** $5 in the up outcome and $0 in the down outcome. The price is 0.4 × $5 ÷ 1.02, or about $1.96. The weights stay the same because you changed the option strike and left the asset model unchanged.

## Apply it to an Umicom project

Design a small synthetic Umicom Trader test table with columns for up/down prices, strike, weight and result. Write one permitted sample and one that fails the weights check. A future application enhancement should make the model assumptions visible with each calculated result.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/pricing-from-cashflows/lessons/05-price-a-one-step-option.html)

[Course contents](index.md) · [Previous lesson — Distinguish a forward delivery price from its value](04-distinguish-forward-price-and-value.md) · [Continue with Financial Instruments Pricing Using C, C++ and Java](../../../courses/financial-instruments-pricing/index.html)
