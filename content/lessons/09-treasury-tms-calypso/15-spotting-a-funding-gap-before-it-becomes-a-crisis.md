# 15. Spot the funding gap before it becomes a crisis

*Treasury Management, TMS and Calypso — From Zero · Practical foundations*

In Chapter 13, Harbour Supplies had £12,000 on Monday morning and several payments to make. The original forecast suggested that it could make the payments, but it would fall below its preferred £5,000 cash buffer on Thursday. If one customer paid late, the forecast even turned negative.

The owner now asks: **“Should we borrow money?”** A good treasury manager cannot answer with a simple yes or no until the purpose, timing, amount, cost and alternatives are clear.

This chapter shows how to identify a *funding gap* and how to compare possible responses without pretending that a forecast is permission to move money.

## Cash shortage and policy shortfall are different

Start with the Thursday balances we calculated earlier:

| Scenario | Forecast Thursday closing cash | Compared with £5,000 buffer |
|---|---:|---:|
| Customer pays on Tuesday | £3,200 | £1,800 below buffer |
| Customer pays the following Monday | −£3,300 | £8,300 below buffer |

In the first scenario, there is still enough **cash on paper** to cover the scheduled payments, but the company's reserve policy would be breached. In the second scenario, the planned payments exceed the available balance by £3,300. Those situations require different conversations. A manager might accept a temporary buffer breach under an authorised policy; a projected negative balance requires a verified funding or payment-change plan before the due time.

A *funding gap* is the difference between what the company expects to have and what it needs for a particular date or period. Be precise about what “needs” means: it might be the minimum amount needed to avoid a missed payment, or a larger amount needed to maintain a safety buffer.

## First find out which numbers can be trusted

The £6,500 customer receipt is a **forecast**. Before arranging a loan, treasury should contact the appropriate team to confirm whether the payment has been initiated or received. A bank credit shown as *settled and reconciled* is stronger evidence than an invoice marked “sent”.

The £3,500 supplier payment has an agreed due date. Treasury may ask whether the supplier would **agree** to a different date. It cannot quietly move the payment and report the problem solved. Wages, taxes and contractual settlement deadlines may have especially strict consequences if delayed.

A useful short checklist is:

1. Which payment is due first, and at what cut-off time?
2. Which incoming funds are settled, confirmed or merely forecast?
3. Are any balances restricted to a particular purpose?
4. Does the organisation have an **approved and currently available** credit facility?
5. What would funding cost, including interest and fees?
6. Who is authorised to approve the proposed action?

You do not need special software to ask these questions. The TMS helps keep the answers, amounts and timestamps together.

## Compare three responses

Imagine the customer payment is late and the Thursday forecast is −£3,300. The organisation wants to maintain its £5,000 buffer. Its **illustrative** shortfall to that policy is £8,300.

**Option 1 — confirm the incoming payment.** If the £6,500 arrives in time, Thursday's projected balance becomes £3,200 again. That still breaches the £5,000 buffer, but avoids a negative balance. It may be sensible to confirm the payment before making a costlier decision.

**Option 2 — negotiate a later supplier date.** If the supplier explicitly agrees to move the £3,500 payment to next Monday, Thursday's late-customer scenario becomes **£200** rather than −£3,300. That still fails the £5,000 reserve policy. A postponed bill remains an obligation: the forecast must show it on its **new** agreed date.

**Option 3 — use an approved short-term facility.** The business might borrow enough to protect its cash buffer until receipts arrive. The facility must actually be available, its interest and fees must be considered, and the repayment date must be included in future forecasts. Borrowing creates another future cashflow; it does not make the original problem vanish.

These are **possibilities to investigate**, not instructions to borrow or delay payments. Organisations differ in risk appetite, contractual terms, approval requirements and regulatory obligations.

## Calculate what a short loan costs

Assume the business can borrow £10,000 for **7 days** at a fixed rate of **6% per year**, with simple interest on an Actual/365 basis and no fees. Chapter 14 gave us the calculation:

> £10,000 × 0.06 × 7 / 365 = **£11.51** interest (rounded)

The borrower receives £10,000 initially and owes approximately **£10,011.51** at maturity under those assumptions. Do not compare this £11.51 alone with the benefit of staying open: fees, borrowing conditions, operational risk and future cash availability all matter. What if the customer pays even later than expected? The cash forecast must include the loan repayment date and a contingency for that possibility.

## How funding appears in a Treasury Management System

A TMS may keep separate records for **bank balances**, **expected business receipts**, **approved payments**, **funding contracts** and **projected closing balances**. If a loan is agreed, the drawdown is an expected inflow and the repayment is an expected outflow. Those projections should later be matched to actual bank activity.

In Calypso-style processing, a loan or deposit is a **financial product and trade**, not just two editable balance figures. The contract has parties, an owning book, currency, dates, interest conventions, workflow and settlement obligations. A downstream process may create payments, confirmations and accounting entries. Changing one date can affect several parts of that chain.

The TMS must also distinguish an **expected facility drawdown** from cash that has actually arrived. A “drawdown requested” status does not make funds spendable.

## Try it yourself

**Exercise A.** Using the original on-time forecast, how much extra cash is needed by Thursday to maintain the £5,000 buffer? Is that the same as the amount needed to avoid a negative balance?

**Exercise B.** With the customer late and the supplier paid as planned, what is the minimum extra amount needed to bring Thursday's balance to £0? How much to bring it to £5,000?

**Exercise C.** Suppose a £10,000 loan arrives on Wednesday and is repaid the following Wednesday. Which dates must appear in your cash ladder? Name at least two items besides the borrowed principal that must be checked.

### Check your answers

**A:** **£1,800** is needed to satisfy the buffer. No additional cash is needed merely to keep Thursday's projected balance non-negative in the on-time scenario.  
**B:** **£3,300** brings −£3,300 to zero, and **£8,300** brings it to £5,000. The appropriate target depends on policy and obligations.  
**C:** Record the actual loan drawdown date as an inflow and the repayment date as an outflow. Check the interest/fees, contractual terms, approvals and what happens if the expected customer money does not arrive.

**Next:** Treasury often deals with cash in more than one currency. We will return to the foreign-exchange forward from Chapter 8 and learn how an FX swap creates **two sets** of cash movements on different dates.
