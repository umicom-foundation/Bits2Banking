# Blockchain Lesson 010 — Contrast permissioned consensus, Raft and BFT

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **contrast permissioned consensus, raft and bft** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Permissioned systems restrict who may validate or order entries. Raft-style consensus addresses crash failures among known replicas. Byzantine fault tolerant (BFT) protocols address some actively faulty or malicious replicas under stricter quorum and communication assumptions. Hyperledger Fabric separates endorsement, ordering and transaction validation and supports different ordering configurations.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A common partially synchronous BFT quorum pattern requires n≥3f+1 replicas to tolerate f Byzantine replicas. If f=1, n must be at least 4. By contrast, a three-node crash-fault-tolerant majority system can continue when one node crashes, but that fact alone offers no Byzantine guarantee.

## Limitations and misconceptions

The n≥3f+1 formula belongs to a particular class of BFT models, not every consensus protocol. A deployment must document membership changes, network partitions, safety and finality.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Why is a three-node Raft example not automatically equivalent to three malicious-tolerant validators?

<details><summary>Reveal the worked answer</summary>

Raft’s standard fault model covers crashed or unavailable replicas, not arbitrary malicious messages. Byzantine tolerance needs additional authenticated protocols and different quorum assumptions.

</details>

## Primary research or standard

- [Hyperledger Fabric: ordering service, endorsement and commitment](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

[Previous](009-explain-proof-of-stake-and-economically-enforced-finality.md) | [Next](011-investigate-smart-contracts-oracles-and-attack-surfaces.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
