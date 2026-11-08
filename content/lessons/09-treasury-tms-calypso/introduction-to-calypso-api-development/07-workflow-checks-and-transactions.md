# Separate workflow checks from updates

## A workflow transition

A workflow describes which state changes are allowed. A trade may be captured before another role approves it. A rule can refuse a transition, but a rule that secretly changes data during validation creates surprising outcomes when another rule rejects the same transition.

The supplied developer guide describes WfTradeRule, WfTransferRule and WfMessageRule callbacks. Its check phase is for validation; its update phase performs authorized changes within the server's workflow transaction. Exact method signatures must come from your licensed release.

## Trace the transaction boundary

The guide distinguishes an existing database connection supplied to server callbacks from a remote client context. It illustrates TradeSQL access inside the supplied transaction and RemoteTrade access for a client. This is not permission to connect a desktop tool directly to the product database.

For an original custom rule, first write its business contract: required fields, permitted state, refusal explanation and intended side effects. Then inspect the SDK interface and the server's transaction ownership. Do not call commit or rollback on a transaction owned by the workflow engine.

## Worked scenario

Rule A checks that a legal entity has settlement instructions. Rule B checks a limit. If A writes an audit row in check and B rejects, the audit row may suggest that a transition happened when it did not. Keep validation free of business mutation. Place approved changes in the appropriate update boundary, with audit meaning defined for accepted versus refused transitions.

## Exercise and answer

A developer adds an event directly during check to notify another system. Why is this unsafe? Answer: another rule may still reject, so an external effect can escape a transaction that never succeeds. The guide describes attaching events through the supported update context; verify the exact release contract before implementation.

## Implementation gate

This module intentionally supplies no guessed WfTradeRule override. Obtain the exact interface, produce a minimal compiling extension, then test accept, reject, exception and rollback with approved fixtures. The read-only adapter cannot qualify transaction-writing code.

[Course contents](index.md)
