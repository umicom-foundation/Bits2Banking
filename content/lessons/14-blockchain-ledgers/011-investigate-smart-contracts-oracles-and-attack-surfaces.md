# Blockchain Lesson 011 — Investigate smart contracts, oracles and attack surfaces

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **investigate smart contracts, oracles and attack surfaces** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A smart contract is deterministic logic executed under a ledger’s validation rules, often updating assets or state. An oracle supplies external observations, such as exchange rates or training-evaluation scores. Contracts cannot infer whether an external fact is true merely because an oracle recorded it. Access controls, replay/nonce rules, upgrade governance and economic incentives remain essential.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A contract promises 10 reputation points when an approved model update passes independent evaluation. An untrusted node claims “loss improved by 0.1”. The contract cannot validate that claim without a trusted evaluator, reproducible evidence or an explicit proof mechanism. A signed oracle statement gives a known provenance, not mathematical truth.

## Limitations and misconceptions

Public smart-contract logs are durable and widely copied. Avoid storing confidential gradients, customer identifiers or private data on-chain. A revocation policy cannot literally erase every historic replica.

### Connection to Umicom

Financial accounts, payments, model checkpoints and training logs share some integrity primitives, but each has distinct policies and record schemas. Use the established Framework data, security, messaging and record-chain services. The educational audit experiment is a single-process hash chain, not a deployed consensus network.

## Exercise — test your understanding

**Question:** Is a signed oracle report always sufficient evidence that a worker performed legitimate training?

<details><summary>Reveal the worked answer</summary>

No. It authenticates who reported the result. Evaluation methodology, data rights, training execution and fraud assumptions still require independent checks.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Previous](010-contrast-permissioned-consensus-raft-and-bft.md) | [Next](012-choose-a-ledger-architecture-for-ai-and-finance.md) | [Course route](../../courses/blockchain-ledgers/index.html)

*Service to Many Leads to Greatness.*
