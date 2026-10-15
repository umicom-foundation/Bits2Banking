# 4. Accounts, balances, currencies and dates

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

One of the easiest ways to make a serious financial mistake is to write down a number without saying *what it measures*. A treasurer needs more than an amount. They need the currency, account, date and current status.

Consider the kitchen's two accounts: one contains £1,000 and the other contains $500. Are its funds “1,500”? No. The numbers use different currencies, so adding them would be as misleading as adding five litres to three metres.

## Treat money as an amount with a currency

A **currency code** tells us the monetary unit: GBP for pounds sterling, USD for US dollars and EUR for euros. A real system usually records monetary amounts with decimal or fixed-point rules suitable for the currency and business operation.

To compare different currencies we need an **exchange rate** with a clearly stated direction and observation time. Suppose the teaching rate is **1 GBP = 1.25 USD**. Our $500 is worth £400 at that rate because $500 ÷ 1.25 USD per GBP = £400. The converted teaching total would be £1,400. It is not a guarantee that the bank would exchange at this rate or charge no fees.

We must retain the original USD balance and the rate used. If the rate changes tomorrow, the reported value in pounds changes even when the number of dollars remains the same.

## There is more than one kind of date

A payment record may have several important dates:

| Date | Meaning in everyday language |
|---|---|
| Instruction date | When somebody entered the payment instruction |
| Approval date | When an authorised person approved it |
| Value or settlement date | When the payment is intended to take financial effect |
| Bank posting date | When the bank recorded it on the account |
| Report date | The date for which the treasurer is preparing the picture |

Different banking products and jurisdictions apply specific date conventions; these definitions are an introduction, not a universal payment rule.

Imagine a supplier payment approved on Monday for settlement on Thursday. A Tuesday report must not claim that the account has already been debited unless bank evidence supports it. It can, however, include the payment in Thursday's forecast.

## Account balance and available balance

The **account balance** is what the institution currently reports according to its terms and posting rules. **Available funds** may differ because of pending items, holds, overdraft permissions or reserved balances. The treasury system should show which figure is being used, instead of giving both the same label.

For instance, an account may show £2,000 while £800 is subject to a hold. Under a simple teaching assumption that there are no other restrictions or facilities, the spendable amount would be £1,200. In a real bank the available-balance calculation comes from the institution's rules and authoritative service.

## Reconciliation: does our record agree with the bank?

Suppose the TMS shows a £750 supplier payment as settled, but the bank statement has no matching movement. The treasurer should not silently mark the bank as wrong or send the payment again. The difference needs an investigation: Was the payment rejected, delayed, routed to another account or simply absent from the latest statement?

**Reconciliation** is the process of comparing two records, identifying differences and explaining them. In cash management, those records often come from the TMS and the bank. A match needs more than equal amounts: currency, date, account, reference and transaction identity can all matter.

## Try it yourself

A fictional charity has **£2,000** in account A and **$1,250** in account B. The teaching rate is 1 GBP = 1.25 USD. A £300 payment from A is due on Thursday.

1. What is the combined teaching value expressed in GBP before Thursday's payment?
2. What is account A's forecast balance after Thursday's payment?
3. What is wrong with calling the payment “settled” on Monday just because it was approved?

**Answers:** $1,250 represents £1,000 at the stated rate, so the combined illustrative value is £3,000. Account A's forecast becomes £1,700. Approval permits processing, while settlement requires evidence that the bank movement took effect.

Now we can examine the people and teams responsible for a financial transaction as it moves from agreement to settlement.

*Reading connection: **Calypso Development and TMS Practical Refresher**, Chapters 1–3; **Volume 12**, Chapter 3 on financial values and dates.*
