# Blockchain Lesson 007 — Understand peer networking, forks and finality

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **understand peer networking, forks and finality** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A peer-to-peer system exchanges candidate blocks or transactions among independent computers. Concurrent proposals, message delays and Byzantine actors can produce different local views of the latest accepted state. A consensus protocol and fork-choice rule resolve or constrain those views. Finality is the condition under which an accepted event can no longer be reversed under the protocol’s stated assumptions.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A and B see block X first while C temporarily sees competing block Y. Without a network-wide rule, each replica can truthfully report a different local head. A chain-selection protocol decides the canonical continuation; a finality rule specifies when the choice becomes settled.

## Limitations and misconceptions

Network broadcast is not consensus. Eventual availability, crash fault tolerance and Byzantine fault tolerance are distinct properties. Finality guarantees depend on protocol and assumptions.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Does a hash-linked list shared by three peers guarantee that all three agree on its latest entry?

<details><summary>Reveal the worked answer</summary>

No. Hash linkage detects mutations within a selected history. Agreement requires a consensus protocol that handles conflicts, ordering and faults.

</details>

## Primary research or standard

- [Ethereum documentation: consensus, fork-choice and sybil resistance](https://ethereum.org/developers/docs/consensus-mechanisms/)

## Continue learning

[Previous](006-explain-blocks-merkle-trees-and-inclusion-proofs.md) | [Next](008-derive-proof-of-work-difficulty-and-expected-attempts.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
