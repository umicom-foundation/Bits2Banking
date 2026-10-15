# 11. From a financial agreement to a completed payment

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

A trader agrees to exchange currencies. A back-office team checks the settlement instructions. An engine prepares a payment message. The bank sends or receives funds. Accounting records the financial effects.

These activities are related, but they are not one single operation. Treating them as the same thing makes support problems much harder to understand.

## Agreement, cashflow and transfer

A **trade** records the financial agreement. A **cashflow** is an amount expected to be paid or received at a particular time. A **transfer** represents a cash or security movement obligation that must be processed operationally.

Return to our fictional FX forward:

| Expected movement | Amount | Direction |
|---|---:|---|
| GBP leg | GBP 100,000 | Outgoing |
| USD leg | USD 125,000 | Incoming |

The system may generate transfer records representing these obligations. The exact number of records and the processing structure depend on the product, client configuration, netting and settlement arrangements.

A **standing settlement instruction** (often SSI or SDI) helps determine where and through which accounts and agents the money or securities should move. A correct trade with missing or outdated instructions may still fail to settle.

## What is a message?

A **payment message** communicates an instruction or status to another system or institution. A **confirmation** communicates agreed transaction terms. A message may be generated before it is sent; it may be sent before another system accepts it; and it may be accepted before the underlying obligation is finally settled.

For this reason, an operations dashboard should not show a single green tick called “done” for all these different stages.

The original *Calypso Training Presentation* illustrates this on **pages 16–18**, where trades relate to transfers, BO messages, documents and postings. The diagrams are useful because each box describes a distinct business object.

## A missing payment example

Suppose the GBP 100,000 payment instruction has been sent, but the bank has not confirmed settlement. The support team should ask:

1. Is the trade valid and approved?
2. Was the expected cashflow and transfer created?
3. Was the right settlement instruction selected?
4. Was a payment message generated and sent?
5. Did the receiving system acknowledge it?
6. Is there evidence of the actual account movement?

The team must not re-send the instruction blindly. If the bank completed the first payment but the acknowledgement was lost, a duplicate instruction could be dangerous. Any retry must follow the approved idempotency and repair controls.

## Where does accounting fit?

**Accounting** records financial events using accounts and balanced debit and credit entries. A **general ledger** provides an organised record of an entity's financial position and activity.

We will use an easier example than FX settlement to introduce double-entry accounting. Suppose the kitchen has a properly recorded supplier payable of £300. When it pays the supplier, it can reduce the payable by £300 and reduce bank cash by £300. In a simplified journal entry:

| Account | Debit | Credit |
|---|---:|---:|
| Supplier payable | £300 | — |
| Bank cash | — | £300 |
| **Total** | **£300** | **£300** |

The equal totals are a basic control. This is a teaching example; real ledger classifications, posting dates and clearing accounts depend on the organisation's accounting policy.

A message stating “sent” is not enough evidence for the ledger to assume the payment actually completed if the accounting policy requires settled bank evidence.

## Try it yourself

A fictional loan is due to pay £1,000 principal plus £20 interest tomorrow. Write down the expected cashflow total. Then label each of these as **agreement**, **instruction** or **observed outcome**: signed loan contract; outgoing payment message; bank statement debit.

**Answers:** The expected outgoing amount is £1,020. The contract is the agreement, the message is the instruction, and the bank statement entry is evidence of an observed outcome, subject to reconciliation.

The next chapter draws the complete picture and shows how Calypso brings these business objects and processes together.

*Reading connection: **Calypso Training Presentation**, pages 16–18, and **Calypso Development and TMS Practical Refresher**, chapters on transfers, messaging and accounting.*
