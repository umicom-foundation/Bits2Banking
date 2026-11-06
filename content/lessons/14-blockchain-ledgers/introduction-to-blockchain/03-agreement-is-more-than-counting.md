# Agreement is more than counting

[Course contents](index.md) · [Previous: Linking records with hashes](02-linking-records-with-hashes.md)

## Computers can disagree for different reasons

A node may be slow, disconnected, faulty or deliberately dishonest. A protocol is a set of rules for exchanging messages and reaching decisions despite specified failures. A design that tolerates a crash is not necessarily safe against a participant sending contradictory messages.

Before saying a majority approved, define the membership and voting weight. Ten thousand network connections need not mean ten thousand independent people or machines. One operator can create many identities unless admission rules prevent it. This is called a Sybil problem.

```text
membership -> eligible voters -> evidence checks -> decision rule
     |              |                  |                 |
 who exists?   who may vote?     what was verified?   when final?
```

## Separate the questions

1. What makes a participant eligible?
2. How are conflicting messages detected?
3. What evidence must a participant verify before voting?
4. How much faulty voting weight is the protocol designed to tolerate?
5. What happens during a partition, when groups cannot communicate?
6. What evidence permits recovery after communication returns?

For a teaching ledger, start with one explicitly trusted writer and label that assumption. Later simulate multiple nodes and conflicting proposals. Do not describe a local file chain as decentralised consensus.

## Exercise

A system accepts a result when 6,000 of 10,000 identities agree. List two reasons that this count alone does not prove the result correct.

## Explained answer

One operator might control many identities. The voters might all apply the same incorrect verification procedure, or approve without checking. A threshold needs a membership model, a fault model and a precisely defined validation task. Confirming ledger bytes is also different from proving that a machine-learning update improves a model.

## Engineering habit

Write assumptions beside the implementation and create tests for their failure. In Umicom, keep these rules in reusable Framework services and expose clear states to clients: proposed, checked, accepted or rejected. A UI should not collapse all of those into a green success badge.

## Continue learning

[Course contents](index.md) · [Previous: Linking records with hashes](02-linking-records-with-hashes.md)

[Browser edition](../../../courses/introduction-to-blockchain/lessons/03-agreement-is-more-than-counting.html)

## Read the related Umicom source

[Source and context](https://github.com/umicom-foundation/umicom-framework/blob/f00aa3eb0c165ab0ac0107f81e84e4602d79c170/include/umicom/base/sha256.h). This public revision matches the source inspected for this lesson.
