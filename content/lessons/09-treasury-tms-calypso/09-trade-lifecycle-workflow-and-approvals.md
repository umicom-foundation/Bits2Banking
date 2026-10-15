# 9. What happens after a trade is agreed?

*Bits to Banking · Treasury Management, TMS and Calypso From Zero · Umicom Foundation*

We have agreed a forward contract to buy USD 125,000 and sell GBP 100,000. The trader has entered its terms in the system. Can everybody now go home and assume the dollars will arrive in three months?

Not yet. The trade has only begun its **lifecycle**: the sequence of states and actions from creation through its eventual completion, cancellation or termination.

## First, check the agreement

A new trade may need independent verification. Does the system show the correct counterparty? Are the currencies the right way round? Does the recorded settlement date match the agreement? Has the trader used an approved book? A small data-entry error can lead to a large unintended payment.

A **workflow** tells the system which actions may happen from each status. A simplified training workflow might look like this:

| Current status | Action | Next status |
|---|---|---|
| NEW | Verify the agreed terms | VERIFIED |
| VERIFIED | Approve / authorise | AUTHORISED |
| AUTHORISED | Confirm with counterparty | CONFIRMED |
| CONFIRMED | Record successful settlement | SETTLED |

These are **classroom states**, not a claim about the exact workflow configuration used by a particular Calypso client. Real environments can have different names, branches and permissions.

A **status** describes where something currently stands. An **action** asks the system to move it forward. A **rule** checks whether an action is allowed under the business conditions. A **permission** checks whether the person or process is authorised to attempt it.

## Why approval is a separate step

A trader who enters a deal should not automatically be able to approve every control exception, change payment instructions and certify settlement. Different people or services may be responsible for different stages. This is called **segregation of duties**.

Suppose a clerk tries to approve a trade but lacks the required permission. The system should refuse the action and record what was attempted. It must not change the status and then ask for permission afterwards.

## A trade can change after confirmation

Imagine the company and bank discover that the agreed amount should have been USD 120,000, not USD 125,000. Depending on contract and policy, the existing trade may require an approved amendment, cancellation or rebooking. It is not safe simply to edit the displayed number and assume nothing else is affected.

The amendment may change risk and valuations, invalidate an existing confirmation, require cashflow and transfer regeneration, or trigger reversals in accounting. This is why financial systems keep versions and audit history.

A user should be able to answer: *Who changed the trade, when, from which value to which value, and what happened to the downstream instructions?*

## What an event does

In a multi-tier platform, an authorised state change can cause an **event** to be published. An event tells interested services that something happened, for example that a trade has changed. A transfer-processing engine might respond by checking the new trade terms and creating or updating an expected settlement obligation.

Different systems use different event mechanisms. In classic Calypso explanations, the Data Server, Event Server and business engines work together. We will study their responsibilities in Chapter 12.

One event may be delivered again after a failure. A system must not create a second payment simply because it sees the same business instruction twice. We call the design goal **idempotency**: repeated handling of the same event should not create duplicate business effects.

## Follow a mistake through the workflow

Take the USD 125,000 / GBP 100,000 forward from Chapter 8. Suppose it was entered with the wrong counterparty and discovered during verification.

1. Should verification approve it? Explain why.
2. What evidence should be recorded about the rejected or corrected action?
3. If the error is discovered **after** confirmation, what other stages may require attention?

**Check:** The wrong counterparty is a significant defect; the action should be refused or sent for authorised correction. Record the original identifier, version, actor, timestamp, proposed action and reason. After confirmation, review confirmations, cashflows, transfers, accounting, risk and any external messages—not just the trade screen.

Chapter 10 explains why a correct trade can still have a changing market value.

*Reading connection: **Calypso Training Presentation**, conceptual model and workflow sections; **Calypso Development and TMS Practical Refresher**, trade lifecycle and workflow chapters.*
