# 8. Foreign exchange: spot and forward agreements

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

A charity in Britain must buy equipment from an American supplier. The invoice is for **USD 125,000**, payable in three months. The charity keeps most of its cash in pounds. How many pounds should it set aside?

The answer depends on the exchange rate. Treasury teams use **foreign exchange (FX)** transactions to obtain other currencies or reduce uncertainty about future currency payments.

## Read an exchange-rate quotation carefully

Suppose the quoted teaching rate is:

> 1 GBP = 1.25 USD

This means one pound buys 1.25 US dollars at that quoted rate, ignoring transaction costs. We describe it as **1.25 USD per GBP**. To find how many pounds correspond to USD 125,000, divide by 1.25:

> USD 125,000 ÷ 1.25 (USD/GBP) = **GBP 100,000**

Write the currencies next to the numbers. It prevents a common mistake: multiplying when the quotation direction requires division.

## A spot trade versus a forward trade

An **FX spot** transaction exchanges currencies for settlement according to the market's spot-date convention, commonly after a short settlement lag. The exact date depends on the currency pair, holidays and market rules. “Spot” does not necessarily mean the money moves immediately.

An **FX forward** agrees an exchange today for a specified future settlement date. The agreed forward rate determines the contractual amounts. This can help a company plan a future currency obligation even if market rates change before the payment date.

A forward rate is not simply today's spot rate with a random extra charge. It reflects relevant market conventions and pricing factors, including the currencies' interest-rate relationship. The 1.25 rate in this lesson is an **invented contract rate for arithmetic practice**, not a live market quote.

## One agreement creates two obligations

Suppose the charity enters a forward to **buy USD 125,000 and sell GBP 100,000** on the agreed future date.

| Currency | Direction | Contractual amount |
|---|---|---:|
| USD | Charity receives | +125,000 |
| GBP | Charity pays | −100,000 |

The counterparty has the opposite view. The two currency movements require settlement instructions and should be checked independently. If one leg fails to arrive, that is not merely a number-formatting problem: it may create a serious operational exposure.

## What if the market rate changes?

Imagine the market later quotes 1 GBP = 1.30 USD. At that illustrative market rate, USD 125,000 would convert to about GBP 96,153.85. But the charity's forward contract still specifies GBP 100,000 for USD 125,000 unless the contract is amended or terminated through its rules.

That difference is one reason a derivative may have a positive or negative market value after execution. We are **not** pricing the complete forward here: an actual valuation must account for settlement date, interest rates, discounting, market data and other contract details.

## Practice with quotation direction

A fictional supplier requests **EUR 45,000**. Assume, just for the exercise, that 1 GBP = 1.125 EUR.

1. How many pounds correspond to the euro amount at this rate?
2. If the organisation expects to pay in two months, why might it consider a forward?
3. What two currency amounts and directions would you record for a GBP-funded purchase of EUR?

**Answers:** EUR 45,000 ÷ 1.125 = **GBP 40,000**. A forward could help the organisation agree future exchange terms; it does not remove every kind of risk. The organisation would record receiving EUR 45,000 and paying GBP 40,000 under the fictional agreed rate.

The next chapter follows our FX forward after it has been entered into a financial system. We will see why “trade saved” is not the end of the story.

*Reading connection: **Calypso Development and TMS Practical Refresher**, foreign-exchange chapter; **Calypso and TMS Training Manual**, Chapter 6.*
