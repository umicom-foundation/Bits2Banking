# Status, approval and evidence

[Course contents](index.md) · [Previous: Cash, timing and a treasury system](01-cash-timing-and-a-system.md)

## Build on the cash forecast

The previous lesson found when money was needed. This lesson follows the £1,000 supplier payment through a system. A status describes its current stage. A transition is a move from one status to another. A rule decides whether that transition is allowed.

Use a notebook. Draw six boxes labelled Draft, Awaiting approval, Approved, Sent, Settled and Rejected. This is a teaching workflow, not a claim that every treasury product uses these exact names.

## Trace one payment

1. A clerk creates `PAY-001` for £1,000 due Wednesday. The record is Draft. It can still be corrected.
2. The clerk submits it for review. It is Awaiting approval. Submission does not send money.
3. An authorised reviewer checks the beneficiary, amount and due date. Approval records that decision and who made it.
4. An authorised process sends a payment instruction. The status becomes Sent only after that step has evidence; clicking a button alone is not proof.
5. A bank response and the organisation's reconciliation process establish the outcome. Settled means the required settlement evidence has been accepted.
6. A rejection records its reason. A rejected instruction must not silently be treated as settled or resent with a new identity.

An audit trail is the sequence of recorded actions: who acted, what changed and when. Reconciliation compares records from different sources, for example the intended payment and the bank's reported movement. A timestamp helps order observations, but it is not proof that an event happened correctly.

## Separate a command from its result

```text
Command: Approve PAY-001
Inputs:  reviewer identity, payment revision, permission
Checks:  still awaiting approval? authorised? same revision?
Result:  approval recorded OR an explained refusal
Evidence: approval event linked to PAY-001 and its revision
```

This diagram uses pseudocode: a description of an algorithm without the syntax of a particular programming language. A revision identifies a particular saved version. If the amount changes after review, the old approval must not accidentally authorise the new amount.

An interface may show an Approve button. The reusable service must still check the rules, because another interface or integration could request the same operation. This is why Umicom places shared business behaviour in Framework and lets applications present it. A greyed-out button is useful guidance, not a substitute for the service's checks.

The existing lesson `09-trade-lifecycle-workflow-and-approvals.md` extends this idea to financial trades. `11-transfers-payment-messages-and-accounting.md` separates transfers, payment messages and accounting. Those are the next readings after the introductory account and currency chapters; neither should be inferred from a balance display alone.

## Exercise

A payment was approved for £1,000. Someone changes its amount to £1,200 before it is sent. What should happen to the old approval? A second operator then clicks Send twice because the first request appears slow. What information would help prevent two payments?

## Answer and explanation

The old approval applies to the reviewed revision. The changed payment needs the appropriate review again. The service should recognise repeated requests for the same operation using a stable request or instruction identity and preserve the recorded outcome. This property is often called idempotency: retrying the same request must not accidentally perform the business action twice. The exact implementation and bank acknowledgement rules need their own design and tests.

## Continue the existing course

Read the treasury lesson index in order, then complete its Stage 1 workbook. The Stage 2 lessons add a seven-day cash forecast, funding gaps and a full trade lifecycle. Keep a list of unfamiliar words and use the glossary before moving into product-specific screens or programming. No live payment is created by this course.

[Review the prerequisite course](../../../courses/computing-from-the-beginning/index.html).


## Source and further reading

[Read the related Umicom example](../03-how-a-treasury-management-system-helps.md). Path: `content/lessons/09-treasury-tms-calypso/03-how-a-treasury-management-system-helps.md`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Continue the existing treasury lessons and workbooks](../index.md).

[Read this lesson as HTML](../../../courses/introduction-to-treasury-management-systems/lessons/02-status-approval-and-evidence.html).

[Course contents](index.md) · [Previous: Cash, timing and a treasury system](01-cash-timing-and-a-system.md)

Sammy Hegab · Umicom Foundation · Original learning material.

[Next: Follow evidence through a payment](03-follow-evidence-through-a-payment.md)
