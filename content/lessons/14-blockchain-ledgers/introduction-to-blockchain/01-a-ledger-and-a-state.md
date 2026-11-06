# A ledger and a state

[Course contents](index.md) · [Next: Linking records with hashes](02-linking-records-with-hashes.md)

## Start with a record you can read

A ledger records changes. State is the result of applying accepted changes. If a practice account starts at zero, receives 10 units and pays 3, its balance is 7. The list of events and the balance answer different questions: how did we get here, and what is true now?

```text
events:  receive 10 -> pay 3
state:       10    ->    7
```

Blockchain systems group records into blocks and link them cryptographically. That structure can help detect altered history. It does not automatically make input data truthful, private or useful. If a sensor reports a wrong reading, storing the reading in a block preserves the wrong reading unless other validation catches it.

## Choose rules before a technology

1. Decide what one record means: payment, inventory movement or document revision.
2. Decide who may propose a record.
3. State the conditions under which it is valid.
4. State what changes when it is accepted.
5. State who needs to agree and which failures the design must tolerate.

For one trusted application on one computer, a conventional transactional database may already meet the need. Independent organisations that cannot rely on one writer pose a different problem. Naming a file blockchain does not answer that problem.

## Exercise

A stockroom begins with 4 components, receives 6 and issues 3. Write the event list and final state. A colleague proposes an issue of 20. What should validation do before changing the state?

## Explained answer

The final quantity is 7. Reject the proposed issue of 20 if the rules forbid negative stock. Leave both the accepted event list and current state unchanged. Writing a rejected event into an audit log is possible, but label it rejected; it must not become an accepted stock movement.

## Umicom connection

Framework should own reusable encoding, persistence and validation contracts. A product chooses its business rules. The SHA-256 API linked below is one building block; it is not a ledger service or a consensus implementation by itself.

## Continue learning

[Course contents](index.md) · [Next: Linking records with hashes](02-linking-records-with-hashes.md)

[Browser edition](../../../courses/introduction-to-blockchain/lessons/01-a-ledger-and-a-state.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
