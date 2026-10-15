# 6. Products, trades, books and legal entities

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

Financial software uses words that sound familiar but have precise meanings. A **product** is not a carton on a shop shelf; in this context it is a type of financial instrument. A **book** is not something you read; it is an organisational place where a bank groups trading activity.

We will learn these ideas using the FX forward from Chapter 5. This is one of the most helpful ways to understand Calypso's conceptual model before seeing any programming code.

## Product: what sort of agreement is this?

A financial **product** describes the kind of contract or instrument. Examples include a bond, a currency forward, a loan and an interest-rate swap. The product determines the important terms and processing rules.

Some financial products, such as a particular government bond, can be traded many times. Others are individually negotiated contracts with terms specific to a deal. In both cases, a useful system separates the description of the instrument from the particular transaction involving it.

## Trade: what did these parties agree to do?

A **trade** is a recorded transaction between parties. For our forward, the trade says that one side will receive USD 125,000 and pay GBP 100,000 on a specified future date. It has an identity and an audit history.

A trade is therefore not simply its product type. Two people can trade the same bond on different dates, at different prices and in different quantities. The product may be the same; the trades are distinct.

This difference is important when somebody asks, “Which transaction should we amend?” Changing one trade must not silently rewrite every trade involving the same product.

## Legal entity: who is legally involved?

A **legal entity** is an organisation or recognised legal unit that can take part in a transaction. The **counterparty** is the other party to the trade. The bank's own trading business is often identified as the **processing organisation (PO)** in classic Calypso terminology.

A bank might have several legal entities for different countries or businesses. Entering the wrong entity can cause serious problems: the contract may name the wrong party, the settlement account may be wrong, and exposure may be attributed incorrectly.

## Book: where does the organisation record the trade?

A **trading book** groups trading activity for a particular business purpose. Our fictional bank might use `LONDON_FX` for the London foreign-exchange desk. Another book might hold bond trades. A book is associated with an owning organisation and may be included in one or more **book hierarchies** for reports and risk aggregation.

An **accounting book** supports the organisation of accounting rules and postings. It is not identical to the trading book. The original presentation distinguishes these concepts because one trading book can be included in wider reporting hierarchies or mapped into an accounting grouping.

## Put the four terms together

| Question | Answer in our fictional FX example |
|---|---|
| What instrument? | FX forward (**Product**) |
| What specific agreement? | Receive USD 125,000, pay GBP 100,000 (**Trade**) |
| Where is it recorded? | `LONDON_FX` (**Trading Book**) |
| Who is involved? | Fictional Bank A and Corporate B (**Legal Entities**) |

Those pieces should agree. A valid-looking amount and date are not enough when the counterparty or book is wrong.

## The original Calypso diagrams are worth studying

In the supplied *Calypso Training Presentation*, the diagrams on **pages 9–15** explain product, trade, legal entity, trading book, book hierarchy and accounting book in a connected model. Study the arrows: they answer whether an item describes an instrument, a transaction, an owner or a reporting grouping. The diagrams represent a classic Calypso conceptual view, so we will check release-specific details later.

## Check your understanding

A fictional bank buys the same government bond in two separate transactions: 100 units on Monday and 200 units on Wednesday. Both are booked to the same fixed-income desk.

1. Is this one trade or two?
2. Can the two trades refer to the same product?
3. What does the book tell us, and what does it *not* tell us?

**Answers:** There are two trades, each with its own identity and terms. They may refer to the same bond product. The book tells us how the bank organises and owns the activity; it does not replace the trade's counterparty, quantity, price or settlement obligations.

The next chapter introduces deposits and loans—two products that are easier to understand before we investigate complex derivatives.

*Reading connection: **Calypso Training Presentation**, pages 9–15, and **Calypso Development and TMS Practical Refresher**, Chapters 3–5.*
