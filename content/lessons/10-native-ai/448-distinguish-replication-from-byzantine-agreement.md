# LLM Lesson 448 — Distinguish replication from Byzantine agreement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **distinguish replication from byzantine agreement** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Replicating an audit log improves availability but does not determine which competing append is canonical. Consensus defines ordering, membership and fault responses. Raft usually assumes crash faults; BFT assumes malicious replicas within declared limits.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Three replicas with one crash can still maintain a majority in an ordinary Raft configuration. One malicious replica may lie about its state; CFT assumptions alone do not protect against this.

## Limitations and misconceptions

Do not claim that the current Framework record-chain API performs consensus or secure replication.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Does placing the same SHA-256 log on three disks implement consensus?

<details><summary>Reveal the worked answer</summary>

No. Disk copies are replication; a consensus protocol is needed to agree on ordering under concurrent proposals and faults.

</details>

## Primary research or standard

- [Hyperledger Fabric: ordering service, endorsement and commitment](https://hyperledger-fabric.readthedocs.io/en/latest/orderer/ordering_service.html)

## Continue learning

[Previous](447-introduce-merkle-proofs-as-compact-inclusion-evidence.md) | [Next](449-estimate-proof-of-work-security-and-verification-costs.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
