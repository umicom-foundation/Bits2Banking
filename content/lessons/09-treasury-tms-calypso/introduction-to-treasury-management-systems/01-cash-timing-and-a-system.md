# Cash, timing and a treasury system

[Course contents](index.md) · [Next: Status, approval and evidence](02-status-approval-and-evidence.md)

## The question this course answers

Can an organisation make the payments it has promised, on the dates they are due? Treasury is the work of managing the money needed to answer that question. A treasury management system, shortened to TMS, records the information and helps people follow controlled processes. It does not make a forecast come true.

You need a notebook and basic addition and subtraction. No trading account, software installation or programming knowledge is required. All amounts below belong to an invented business and are in pounds. They are not advice about managing a real organisation.

## Follow a small business through three days

A workshop starts Monday with £800 in its bank account. A customer is expected to pay £400 on Tuesday. The workshop owes a supplier £1,000 on Wednesday. A balance is the amount recorded in an account at a particular time. A cashflow is money arriving or leaving. A forecast uses expected cashflows to estimate future balances.

```text
Day          Opening   Expected in   Expected out   Forecast closing
Monday          800             0              0                800
Tuesday         800           400              0              1,200
Wednesday     1,200             0          1,000                200
```

Read each row from left to right. Closing balance equals opening balance plus incoming money minus outgoing money. The next day's opening balance is the previous day's closing balance. A closing balance of £200 is a forecast here, not a statement that the bank has confirmed a payment.

Now suppose the customer pays on Thursday instead. Wednesday becomes £800 minus £1,000, which is minus £200. The workshop has a funding gap: a payment is due before enough money is expected to be available. Having a profitable order does not by itself solve a timing problem.

## What information should the system keep?

For the £1,000 payment, record the supplier, account, currency, amount and due date. Also record whether it is only planned, approved for payment, sent to a bank, or confirmed as settled. An identifier such as `PAY-001` helps people refer to the same payment without relying on a description that may change.

```text
Commitment → forecast → review → approved instruction → bank response
    £1,000    Wednesday    who?       PAY-001             accepted?
```

An obligation is something the business owes. An instruction asks another system to act. Evidence is the information showing what actually happened. These are related records, not interchangeable names for one event.

The existing Bits2Banking treasury lessons follow this financial story into accounts, departments and trade processing. Their source files live in `content/lessons/09-treasury-tms-calypso`. Begin with `01-what-is-money-and-what-does-a-bank-do.md` if the meaning of an account or bank is still unfamiliar. No Umicom TMS build is needed for the arithmetic.

## Exercise

The customer now pays £250 on Tuesday and the supplier payment remains £1,000. Calculate Wednesday's forecast closing balance. Then move that £250 receipt to Thursday and calculate the amount missing on Wednesday. Name one extra field needed if the supplier invoice is in euros instead of pounds.

## Answer and explanation

With the Tuesday receipt: £800 + £250 − £1,000 = £50. With a Thursday receipt: £800 − £1,000 = −£200 on Wednesday. Currency is an essential extra field. You cannot add £800 and €250 as though they were the same unit; a conversion needs an exchange rate and a clear valuation date. Currency conversion is a later lesson.

## Check your understanding

If your answer differs, write each day's opening balance before adding that day's flows. Do not include Thursday's receipt in Wednesday's available money. Keep expected and confirmed amounts separately labelled. Next, follow the status of one payment to see why a saved record is not proof of settlement.

[Review the prerequisite course](../../../courses/computing-from-the-beginning/index.html).


## Source and further reading

[Read the related Umicom example](../03-how-a-treasury-management-system-helps.md). Path: `content/lessons/09-treasury-tms-calypso/03-how-a-treasury-management-system-helps.md`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Continue the existing treasury lessons and workbooks](../index.md).

[Read this lesson as HTML](../../../courses/introduction-to-treasury-management-systems/lessons/01-cash-timing-and-a-system.html).

[Course contents](index.md) · [Next: Status, approval and evidence](02-status-approval-and-evidence.md)

Sammy Hegab · Umicom Foundation · Original learning material.
