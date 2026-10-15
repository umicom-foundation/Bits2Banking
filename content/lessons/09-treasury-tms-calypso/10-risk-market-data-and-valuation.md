# 10. Why the value of a trade can change

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

Imagine that the kitchen's financial adviser checks a foreign-currency position on two different days. The amount of dollars has not changed, yet the reported value in pounds is different. Is somebody's calculation necessarily wrong?

Not at all. Market prices move. A trade or asset can change in reported value even when its contractual terms stay the same.

## Start with one currency holding

Suppose an organisation holds **USD 125,000** and reports its value in pounds. On Day 1, the teaching rate is **1 GBP = 1.25 USD**. The holding is worth GBP 100,000 at that rate. On Day 2, the teaching rate becomes **1 GBP = 1.30 USD**. Now it is worth approximately GBP 96,153.85.

The pound value has fallen by about **£3,846.15**. No dollars were sent or received. Only the exchange-rate assumption changed.

This example values a simple USD holding. It is **not** a complete valuation of the FX forward in Chapter 8, because a forward includes both contractual currency legs and their future settlement date.

## What is market data?

**Market data** includes exchange rates, interest rates, bond prices, commodity prices and other information used in financial decisions and valuation. A rate is not useful without context. We need to know its currency pair, quotation direction, source and observation time.

If a feed stopped updating yesterday, a screen might still display the last value. That number looks normal until somebody asks, “When was it last refreshed?” A robust system distinguishes *present data* from *fresh and suitable data*.

Market data feeds can also disagree. Before labelling a price wrong, an analyst should compare the timestamp, source, market convention and instrument being priced.

## Valuation, profit and risk are related—but different

**Valuation** estimates what an asset or contract is worth at an agreed time using a defined method and inputs.

**Profit and loss (P&L)** describes financial gains and losses. A change in valuation may contribute to P&L, but cashflows, fees, trades, accounting conventions and other events can also affect it.

**Risk** asks what could happen if market conditions or counterparties change. For a USD position, one risk is the movement in GBP/USD. For a fixed-rate bond, interest-rate changes affect value. For a loan, borrower default creates credit risk.

You do not need to memorise advanced risk formulas yet. First learn to ask the right questions:

- Which financial object is being valued?
- In which currency is its value reported?
- Which market data and valuation date were used?
- What happens if the exchange rate or interest rate moves?
- Who checks the result independently?

## A simple risk scenario

A company expects to receive USD 125,000 next month. At 1.25 USD per GBP, the illustrative pound value is £100,000. If the rate changes to 1.30, the same dollars have a lower pound value. If it changes to 1.20, they have a higher pound value—about £104,166.67.

A treasury team can use such scenarios to understand its currency exposure and decide whether a hedge is appropriate. A hedge can reduce a chosen exposure, but it may introduce contractual costs and other risks.

## Try it yourself

A fictional organisation holds **USD 12,500**. Compare its GBP value using 1.25 USD per GBP and 1.00 USD per GBP. Which exchange-rate move makes the dollar holding worth more pounds?

**Answers:** USD 12,500 ÷ 1.25 = **GBP 10,000**. At 1.00 USD per GBP it becomes **GBP 12,500**. The latter rate gives a higher GBP value to the same USD holding.

Make a small report with the original USD amount, each teaching rate, resulting GBP value and valuation date. Explain why a report without the rate and date cannot be reproduced reliably.

The next chapter distinguishes an economic contract from the transfers, messages and accounting records used to complete it.

*Reading connection: **Calypso and TMS Training Manual**, risk and valuation chapters; **Volume 12**, financial values; **Calypso Development and TMS Practical Refresher**, Chapter 9.*
