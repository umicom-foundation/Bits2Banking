# 14. When money earns interest: deposits, loans and the calendar

*Treasury Management, TMS and Calypso — From Zero · Practical foundations*

Harbour Supplies has survived a busy week. A larger customer then makes an early payment, leaving the business with spare cash that it does not expect to need for a month. The owner asks whether some of it could earn interest. The finance team must answer a second question before arranging anything: **“Exactly when do we need this money back?”**

This lesson introduces a *deposit* and a *loan*, shows how simple interest is calculated, and explains why an apparently small difference in date conventions can affect financial results.

## Two sides of the same arrangement

Suppose the business places **£60,000** with a bank for 30 days. To the business, this is a **deposit**: it has temporarily provided money and expects to receive the principal back, plus the agreed interest, at maturity. To the bank, that cash is a liability it must repay under the contract.

Now reverse the direction. If Harbour Supplies borrows £60,000 from the bank, the company has a **loan**. The company receives money now and promises to repay it, usually with interest. The economic direction matters more than the word used on a screen.

We need four pieces of information to start a simple-interest calculation:

| Term | Meaning | Teaching example |
|---|---|---|
| Principal | The amount deposited or borrowed | £60,000 |
| Annual interest rate | The interest percentage expressed for a year | 4.8% |
| Interest period | The agreed number of interest-bearing days | 30 days |
| Day-count basis | The rule for turning days into a year fraction | Actual/365 |

The interest rate is written as a percentage. **4.8% = 0.048** as a decimal. Dividing by 100 is not optional; using 4.8 rather than 0.048 would produce a result one hundred times too large.

## Calculate a month's simple interest

For this specific example, we use:

> **Interest = principal × annual rate × days / day-count denominator**

Substitute the values:

> £60,000 × 0.048 × 30 / 365 = **£236.71** (rounded to pennies)

If the deposit repays principal and all interest at maturity, the amount due would be:

> £60,000 + £236.71 = **£60,236.71**

That is a *contractual amount due* in our fictional example. It is **not** proof that the bank has already paid it. A treasury system may distinguish the expected maturity payment from a confirmed instruction and a settled receipt.

The example assumes a fixed rate, simple interest, no fees, no tax deduction and a 30-day interest period. Real contracts may use a different rate convention, payment schedule, holiday adjustment or compounding rule. Those must come from the agreed instrument terms, not from a convenient formula found online.

## Why does the calendar matter?

You might reasonably ask why the formula divides by 365. Some money-market contracts use **Actual/360**; others use **Actual/365** or a form of **30/360**. These are *day-count conventions*: rules for calculating the fraction of a year to which the rate applies.

For the same 30 actual days, principal and rate:

| Basis | Calculation | Interest |
|---|---|---:|
| Actual/365 | £60,000 × 0.048 × 30 / 365 | **£236.71** |
| Actual/360 | £60,000 × 0.048 × 30 / 360 | **£240.00** |

The £3.29 difference comes from a contractual convention, not a computing error. An incorrect convention can make every accrued amount wrong, which matters when hundreds of transactions are processed together.

The word *actual* means that the calendar days in the interest period are counted, subject to the instrument's exact rules. It does **not** mean that the bank necessarily uses the account balance shown on your phone each day. The deposited amount, start date, maturity date and rate-setting rules belong to the contract.

## Interest earned is not always interest received

Imagine the deposit starts today but matures in 30 days. The business may calculate how much interest has *accrued* (built up) after ten days. It has not necessarily received any cash yet.

For the fictional Actual/365 deposit, ten days of simple accrual would be:

> £60,000 × 0.048 × 10 / 365 = **£78.90**, rounded for display

That figure is useful for valuation or accounting. The bank account still does not contain that interest unless it has actually been paid. A system must keep **accrual**, **cashflow due** and **settlement** distinct.

## What can go wrong with an apparently simple deposit?

Suppose the business schedules payroll before the deposit matures. The deposit might be an asset worth £60,000, but it may not be available to make that day's payment. Early withdrawal could be unavailable or subject to penalties. Treasury needs both a **cashflow forecast** and knowledge of whether the cash is **accessible when required**.

Before entering such a transaction into a Treasury Management System, a user or developer should check the counterparty, currency, trade date, start/value date, maturity date, principal, rate, day-count convention, repayment terms and settlement instructions. The system should not silently invent missing conventions.

## Try it yourself

**Exercise A.** A company borrows **£10,000** for **7 days** at a fixed annual simple rate of **6%**, using Actual/365. Ignoring fees, calculate the interest and the maturity repayment.

**Exercise B.** A £60,000 deposit matures on Friday, but wages must be paid on Thursday. Is it safe to add the deposit's maturity amount to Thursday's available cash? Explain.

**Exercise C.** Two systems calculate different interest on the same deal. One uses Actual/360 and the other Actual/365. What information should you inspect before deciding that either one is wrong?

### Check your answers

**A:** £10,000 × 0.06 × 7 / 365 = **£11.51** when rounded to pennies; maturity repayment **£10,011.51** under the stated assumptions.  
**B:** No. Cash due Friday is not available on Thursday unless the terms provide a confirmed, usable source of funds before then.  
**C:** Inspect the legal terms, the correct start/end dates and day-count convention, the rate and any holiday or compounding rules. Compare both calculations with those contract terms.

**Next:** a company can have a healthy bank balance today and a funding shortfall tomorrow. We will use cash forecasts and the cost of borrowing to understand how treasury makes that decision.
