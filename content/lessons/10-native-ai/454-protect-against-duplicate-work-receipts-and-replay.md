# LLM Lesson 454 — Protect against duplicate work receipts and replay

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **protect against duplicate work receipts and replay** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

A duplicate result can be authenticated and byte-identical to an earlier result. Idempotency keys, round-scoped worker sequences, durable replay state and ticket checks prevent a second aggregation of the same samples. The existing in-process FederatedJob tickets are not durable network credentials.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

A coordinator accepts a delta from round 3, sequence 7. It crashes, restarts and receives the same frame. Without persisted deduplication it may count 100 samples twice; an audit event should link the replay to the original and not re-apply the update.

## Limitations and misconceptions

Append-only receipt history is necessary evidence in some systems but is not itself a complete replay-prevention state machine.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** Which property must survive process restart to prevent duplicate acceptance?

<details><summary>Reveal the worked answer</summary>

An authenticated durable mapping of already-used round/worker/sequence identifiers to their accepted outcomes.

</details>

## Primary research or standard

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Previous](453-trace-signed-receipts-to-authorised-worker-identities.md) | [Next](455-measure-ledger-overhead-separately-from-training-cost.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
