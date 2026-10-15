# 7. Deposits, loans and simple interest

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

A business sometimes has extra money for a short period. At other times, it needs to borrow. Treasury teams manage both situations using instruments such as deposits and loans.

To understand the basic arithmetic, we will follow a fictional deposit without any bank account or trading system.

## Principal, interest and maturity

The **principal** is the starting amount placed on deposit or borrowed. **Interest** is the amount paid for the use of the money, calculated according to the contract. **Maturity** is the date on which the agreement is due to end or the principal is due to be returned.

Imagine the kitchen deposits **£10,000** for 90 days at an annual rate of **5%**, using a simple-interest calculation and an **Actual/365** day-count rule. “Actual/365” means we count the agreed actual days and divide by 365 for this calculation.

The formula is:

> Interest = Principal × annual rate × days ÷ day-count denominator

Putting in the numbers:

> £10,000 × 0.05 × 90 ÷ 365 = £123.287671…

Rounded to the nearest penny, the example interest is **£123.29**. Assuming there are no fees, taxes or early withdrawals, the maturity receipt is **£10,123.29**.

This is a **teaching calculation**, not a universal bank formula. Real contracts specify their day-count convention, compounding, calendars, rate changes, settlement method and rounding rules.

## Follow the cash movements

For the organisation placing the deposit, the opening transaction moves £10,000 out of an available cash account into the deposit investment. At maturity, the organisation expects its principal back plus interest. A TMS needs to show these movements on their correct dates.

| Stage | Cashflow from the depositor's view |
|---|---:|
| Deposit starts | −£10,000 |
| Deposit matures | +£10,123.29 |

Do not call the opening cash movement an expense or the entire maturity receipt profit. Most of the maturity receipt is the return of principal. In our simple example, the **£123.29 interest** is the additional income before considering accounting and tax rules.

From a borrower's perspective, the signs reverse: the borrower receives principal at the beginning, then pays it back together with interest.

## Why date conventions matter

Two contracts that both advertise 5% per year can produce different amounts if they use different conventions. A calculation on an Actual/360 basis uses 360 rather than 365 in the denominator. With the same illustrative £10,000 and 90 days:

> £10,000 × 0.05 × 90 ÷ 360 = **£125.00**

The difference is **£1.71** for this example. That may seem small, but scale it across thousands of transactions and the choice of convention matters greatly.

## Before a TMS accepts a deposit

A reliable system checks the currency, principal, rate, start and maturity dates, counterparty, applicable calendar and authorised trading book. It should also know whether the deal has been approved and whether the opening cash movement has settled.

A saved trade record alone does not prove the cash has moved. That distinction is essential when treasury forecasts its bank balances.

## Try the calculation

A fictional organisation makes a £5,000 deposit at **4% simple interest** for **30 actual days**, using Actual/365.

1. Calculate the interest before rounding.
2. Round it to two decimal places.
3. State the expected maturity amount.
4. Explain what would be different for a loan instead of a deposit.

**Answers:** Interest = £5,000 × 0.04 × 30 ÷ 365 = £16.438356… or **£16.44** to two decimal places. The maturity receipt is **£5,016.44**. A borrower typically receives the original principal and later owes principal plus interest, according to the contract.

In Chapter 8, we move from one currency to two and examine how an FX forward helps manage a future payment.

*Reading connection: **Calypso and TMS Training Manual**, financial markets and instruments; **Calypso Development and TMS Practical Refresher**, money-market products.*
