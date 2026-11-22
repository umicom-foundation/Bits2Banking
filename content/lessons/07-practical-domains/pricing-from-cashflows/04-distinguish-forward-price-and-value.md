<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/pricing-from-cashflows/04-distinguish-forward-price-and-value.md

PURPOSE:
Read a forward payoff and tell apart the agreed delivery price and the value of an existing contract.

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

# Distinguish a forward delivery price from its value

[Course contents](index.md) · [Previous lesson — Measure a bond price's rate sensitivity](03-measure-an-interest-rate-shift.md) · [Next lesson — Price a call option in a two-outcome model](05-price-a-one-step-option.md)

## What you will learn

Read a forward payoff and tell apart the agreed delivery price and the value of an existing contract.

## Read a simple forward

A **forward** is an agreement made today to buy or sell something at an agreed price on a future date. The contract’s **delivery price** stays fixed for that trade. Its **value** can change when conditions change. The long side agrees to buy. The short side agrees to sell.

For this one-period exercise, suppose an item costs $100 today. It generates no income, costs nothing to store, and can be bought or sold freely. Use a one-period financing rate of 5%, and ignore fees, default and other real complications.

## Work it through

1. Borrow $100 and buy the item. At the end of the period the debt has grown to $105. Holding the item gives you something to deliver. In this model the fair new forward delivery price is $105. A newly entered forward at that price starts with value zero under the model.
2. Suppose you entered a long forward at $105. On delivery day the market price is $112. You pay $105 and receive an item worth $112. Your long payoff is $112 − $105 = $7.
3. If the delivery-day market price is $99, the long payoff is $99 − $105 = −$6. The short payoff has the opposite sign.
4. Before that day, with one whole period left and the same rate, suppose the fair new delivery price is now $110. Your existing $105 contract is worth (110 − 105) ÷ 1.05, or about $4.76 to the long side under the stated model. An offsetting short agreement at $110 would leave a $5 payment in one year.

## Try it and check

Your existing long forward uses a $105 delivery price. At its delivery date, the item is worth $102. What is the payoff to the long and short sides?

**Check:** The long receives a $102 item for $105, so its payoff is −$3. The short has a +$3 payoff relative to the same market price. At the delivery date there is no remaining time to discount.

## Apply it to an Umicom project

Sketch a TMS trade record with separate fields for agreed delivery price, current model value, valuation date and delivery date. Show the side alongside each amount so someone reviewing a negative value knows whose viewpoint it represents.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/pricing-from-cashflows/lessons/04-distinguish-forward-price-and-value.html)

[Course contents](index.md) · [Previous lesson — Measure a bond price's rate sensitivity](03-measure-an-interest-rate-shift.md) · [Next lesson — Price a call option in a two-outcome model](05-price-a-one-step-option.md)
