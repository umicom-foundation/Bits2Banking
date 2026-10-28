# Research Lesson 040 — Write a reproducible cross-institutional ledger research plan

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **write a reproducible cross-institutional ledger research plan** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A scientific design controls initial checkpoint, authorised datasets, participant identities, network topology, threat model, evaluation data, synchronisation policy and statistical repetitions. Compare log-only, permissioned consensus and optional public-chain designs at equal workload.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Pre-register an acceptance gate: no network or consensus design is selected without passing checksum/parity, tamper and replay tests plus a disclosed maximum verification and latency budget. Negative results are legitimate outcomes.

## Limitations and misconceptions

Novelty requires comparison against prior art, not naming a new coin or token.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What evidence would falsify the claim that a blockchain helps this experiment?

<details><summary>Reveal the worked answer</summary>

Equivalent integrity/governance with a signed log at lower cost under the same tested threat model.

</details>

## Primary research or standard

- [SoK: Blockchain-based Decentralized AI](https://arxiv.org/abs/2411.17461)

## Continue learning

[Previous](039-model-ledger-throughput-versus-training-improvement.md) | [Course route](../../courses/ai-research/blockchain-research-evidence.html)

*Service to Many Leads to Greatness.*
