# Treasury From Zero — Stage 2 practice workbook

*Cash forecasting, simple interest, short-term funding, FX swaps, repos and settlement*

This workbook belongs with [Lessons 13–18](index.md). You can complete every financial exercise with a calculator and a notebook. All businesses, rates and dates are fictional. They are for learning, not for making real financial decisions.

A useful habit is to **write down the currency and date beside each amount**. If an answer is wrong, keep the original attempt and add a correction underneath. In financial systems, understanding why a calculation failed is more valuable than hiding the error.

## Practice 1 — Cash arriving too late

A business opens Monday with **£9,000**. It must pay **£5,000** on Tuesday and **£3,000** on Wednesday. It expects a customer to pay **£6,000** on Thursday.

1. Calculate the closing cash for Monday, Tuesday, Wednesday and Thursday. Assume there are no other movements.
2. On which day does cash reach its lowest level?
3. If the company requires a £4,000 cash buffer, which days fall below it?
4. Explain why the Thursday receipt cannot be counted as Tuesday's available cash.

**Try first.** Do not read the answers below until you have a four-row table.

## Practice 2 — Interest belongs to a contract

A company places **£80,000** on a 20-day fixed deposit at **3.65%** simple annual interest on Actual/365.

1. Write the rate as a decimal.
2. Calculate the deposit's interest, rounded to pennies.
3. Calculate the amount due at maturity if all principal and interest are repaid then.
4. Describe how a deposit can earn accrued interest without the bank account having received that interest yet.

## Practice 3 — Spot the funding decision

The company's forecast shows **£2,500** available before a payment of **£4,000** tomorrow. It aims to keep a **£1,000** buffer.

1. What is the closing balance if the payment is made and no new money arrives?
2. How much additional available cash is needed to avoid a negative balance?
3. How much is needed to make the payment and retain the full £1,000 buffer?
4. List two questions you would ask before suggesting borrowing.

## Practice 4 — Two FX swap dates

On the near date, a company receives **USD 50,000** and pays **GBP 40,000**. On the far date, it pays **USD 50,800** and receives **GBP 40,000**.

1. Create a two-row table showing GBP and USD cash movements with + or − signs.
2. Explain why the transactions cannot be recorded as a single ‘net USD 800’ payment.
3. If the near USD receipt is missing, what needs investigating before any repeat instruction?

## Practice 5 — Repo cash and collateral

A fictional seven-day repo supplies **£200,000** of cash at **4.5%** per year, simple interest, Actual/360. The eligible securities are worth **£215,000**, and the haircut is **3%**.

1. Calculate repo interest and the illustrative repurchase price.
2. Calculate the securities' haircut-adjusted value.
3. Is that simplified adjusted value more or less than the cash advanced?
4. Name two changes that might trigger further collateral review during the transaction.

## Practice 6 — A trade that is not finished

A fictional deliverable FX forward is marked *confirmed*. The payment in currency A is settled; the receipt in currency B is still *pending*. A message log shows that an instruction was generated, but there is no final receipt confirmation.

Write a short note for a colleague with three headings: **What is known**, **What is not yet known**, and **What needs checking**. Explain why it is unsafe to mark the whole trade settled or resend a payment without identifying its original message.

---

## Worked answers

### Practice 1

Monday £9,000. Tuesday £9,000 − £5,000 = **£4,000**. Wednesday £4,000 − £3,000 = **£1,000**. Thursday £1,000 + £6,000 = **£7,000**. Wednesday is lowest, and only Wednesday is below the £4,000 buffer; Tuesday is exactly at the buffer. A future receipt cannot settle a payment that becomes due earlier.

### Practice 2

3.65% = **0.0365**. Interest = £80,000 × 0.0365 × 20 / 365 = **£160.00**. Maturity amount under the assumptions = **£80,160.00**. Accrual measures interest earned over the period; settlement is the separate event of actually receiving the cash.

### Practice 3

£2,500 − £4,000 = **−£1,500**. The gap to zero is **£1,500**. The gap to the required £1,000 buffer is **£2,500**. Ask whether the payment date is fixed and whether any incoming funds or an approved credit facility are genuinely available before the due time.

### Practice 4

Near: USD **+50,000**, GBP **−40,000**. Far: USD **−50,800**, GBP **+40,000**. The dates, both currencies and the gross settlement obligations matter; netting these movements into one amount hides a real cashflow and risk. Check the original transfer, settlement details, outgoing message, acknowledgements and bank reconciliation before a repair.

### Practice 5

Interest = £200,000 × 0.045 × 7 / 360 = **£175.00**. Illustrative repurchase price = **£200,175.00**. Adjusted collateral value = £215,000 × 0.97 = **£208,550.00**, which is **£8,550** above the cash advanced under the simplified calculation. A market price decline or a change in collateral eligibility may require review.

### Practice 6

A good note separates economic agreement from operational settlement. State that the trade is confirmed and one cash obligation settled, but the other receipt remains pending. Check the currency B transfer ID, account details, message and acknowledgement history, value date and reconciled bank evidence. Do not create a second business effect or a false final status merely to clear a task from the screen.

## Have you learned the ideas?

After these exercises, you should be able to explain **why cashflow dates matter**, **how a day-count convention affects interest**, **why borrowing creates a future obligation**, **how an FX swap contains two linked currency exchanges**, **what a repo haircut means**, and **why trade confirmation does not prove settlement**.

If one idea is still unclear, return to its lesson and work through the numbers again with different, fictional amounts. Understanding comes from being able to explain the result—not from memorising the sample figures.
