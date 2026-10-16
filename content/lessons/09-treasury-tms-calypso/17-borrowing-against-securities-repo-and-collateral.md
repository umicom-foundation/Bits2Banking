# 17. Borrowing against securities: repos and collateral

*Treasury Management, TMS and Calypso — From Zero · Practical foundations*

Imagine a financial institution needs cash for one week. It owns government bonds that have a market value, but it does not necessarily want to dispose of them permanently. One way to obtain short-term funding is through a **repurchase agreement**, usually called a **repo**.

A repo is easier to understand if you start with what changes hands rather than with its abbreviation. In a common repo structure, one party sells securities for cash and agrees to buy them back later at a specified price. Economically, this often resembles **borrowing cash against securities**, although the legal arrangements and ownership details are governed by the specific contract.

This is an introductory explanation, not legal advice or a live pricing instruction.

## Follow the two sides of a repo

Consider a fictional institution called Harbour Bank. It needs **£1,000,000** for seven days and owns eligible government bonds. Another institution, Riverside Bank, is willing to provide cash against those securities under an agreed repo contract.

On the opening date:

- **Harbour Bank receives £1,000,000 cash.**
- **Riverside Bank receives the agreed securities.**

On the closing date, subject to the agreement:

- **Harbour Bank pays the agreed repurchase price.**
- **Riverside Bank returns the appropriate securities.**

From Harbour Bank's point of view, this is the **repo**. From Riverside Bank's point of view, providing the cash and receiving the securities is generally described as a **reverse repo**. The same transaction therefore has different labels depending on which side you are describing.

## Work out the repurchase price

Assume a seven-day agreement at a fixed **4% annual repo rate**, using **Actual/360** for simple interest. We ignore fees and other special terms for this classroom example.

> Repo interest = £1,000,000 × 0.04 × 7 / 360 = **£777.78**

The illustrative repurchase price is:

> £1,000,000 + £777.78 = **£1,000,777.78**

Notice how the calculation connects to Chapter 14. The *principal*, *rate*, *number of days* and *day-count basis* must all be explicit. A different basis or number of interest-bearing days would change the result.

The repurchase price is **due on the contract's closing date**. It should enter the institution's cash ladder as an outflow on that date. The £1,000,000 received at the opening is not free money: it has created a future repayment obligation.

## Why does collateral have a market value?

The securities matter because they give the cash provider a form of protection if the counterparty does not meet its obligations. But securities prices can change. A security worth £1,050,000 today could be worth less next week.

To allow for that risk, repo transactions commonly apply a **haircut**. A haircut is a percentage reduction applied to a security's recognised value for the purpose of determining how much cash can be advanced against it.

Suppose the collateral has a market value of **£1,050,000**, and the agreed haircut is **2%**. Its illustrative lending value is:

> £1,050,000 × (1 − 0.02) = **£1,029,000**

At this haircut, the recognised value exceeds the £1,000,000 cash advanced. The difference is a safety cushion, not a guarantee that no loss is possible. Eligibility rules, price moves, concentration, settlement delays and contractual protections all matter.

Another way to calculate is to start with the needed cash and ask for the approximate minimum security market value under the same simple rule:

> £1,000,000 ÷ 0.98 ≈ **£1,020,408.16**

The actual required collateral and margin arrangements depend on the contract, valuation terms, eligible securities and agreed margin policy. Our two calculations only explain what a 2% haircut means mathematically.

## What happens if the securities lose value?

Imagine that the agreed collateral loses market value during the week. The transaction may require a **margin call**: one party asks the other to deliver more collateral or cash, according to the agreement. A margin call is not automatically a failed trade. It is part of controlling credit exposure as market prices change.

A Treasury Management System must therefore know more than the cash principal and interest rate. It needs identifiers for the securities, quantity, pricing source, valuation date, haircut, eligible-collateral rules, counterparty, margin status and actual settlement results. A report that says “collateral posted” without the asset identity and amount is not enough for a controlled review.

## Connect the repo to a real treasury problem

Why choose a repo rather than an unsecured loan? A repo may make financing possible on different terms because securities support the arrangement. But it also creates operational work: securities must be available and eligible, moved or held under an agreed mechanism, valued and returned or substituted appropriately.

From a treasury perspective, the repo adds **cash now** and a **cash payment later**. From a securities-finance perspective, it also adds securities-delivery obligations and collateral controls. From an accounting perspective, the treatment depends on applicable standards and the contract's substance and terms. These are related views of the same transaction; they should not be collapsed into one status.

Calypso and other front-to-back platforms can support repo and collateral workflows, but their exact product setup, legal agreements, processing and report configurations depend on the installed module and release. The teaching point is to trace the **cash**, **security**, **agreement**, **margin** and **settlement** separately.

## Try it yourself

**Exercise A.** A bank enters a fictional repo for **£500,000**, ten days, **3.6%** annual simple repo rate, Actual/360. Calculate the interest and repurchase price, assuming no fees.

**Exercise B.** Eligible securities are valued at **£600,000** with a **5%** haircut. What is their illustrative lending value?

**Exercise C.** You are reviewing a repo where the cash has been received but the securities-delivery confirmation is missing. Does the cash receipt prove the complete transaction is operationally settled? What would you check?

### Check your answers

**A:** £500,000 × 0.036 × 10 / 360 = **£500.00** interest; repurchase price **£500,500.00**.  
**B:** £600,000 × 0.95 = **£570,000** recognised lending value under the simplified rule.  
**C:** No. Check the actual securities transfer, settlement instructions, custodian or depository confirmations, matching status and any outstanding exceptions. Keep the cash and securities movements distinct.

**Next:** we will bring deposits, FX and repo back to the central idea of this course: a financial agreement passes through people, controls and systems before its obligations are complete.
