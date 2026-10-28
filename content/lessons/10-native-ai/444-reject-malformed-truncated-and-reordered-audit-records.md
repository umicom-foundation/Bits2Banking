# LLM Lesson 444 — Reject malformed, truncated and reordered audit records

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT · **Language:** UK English

## Learning outcome

Explain **reject malformed, truncated and reordered audit records** using an explicit trust model, identify the supporting mathematics and distinguish conceptual models from tested functionality.

## Concept explained

Before accepting a decoded receipt, validate the record kind, length, reserved bytes, nonzero commitments, outcome code and trusted predecessor. Only publish the new checkpoint and parsed fields when the canonical verifier succeeds. Test failure atomicity for every rejected case.

### Follow the mechanism

1. Identify the authoritative data, model or ledger state and its owner.
2. Separate a byte-integrity check from participant authentication and authorisation.
3. Determine which state-transition rules and fault assumptions the method actually guarantees.
4. Check a worked example and state at least one condition that could invalidate the result.

## Worked example

Modify one byte in the second payload: the SHA-256 payload digest changes. Even if a full record is otherwise structurally valid, verification rejects it against the original committed digest. A swapped record also fails expected predecessor ordering.

## Limitations and misconceptions

A malicious writer could construct an entirely different valid chain from its own genesis; anchoring and authorisation are separate.

### Native software and research boundary

Use Framework-owned C23 numerical, messaging, identity and record-chain components. Applications remain thin consumers. Hypothetical peer, blockchain and optimiser functions are concepts until integrated and independently qualified.

## Exercise — test your understanding

**Question:** What should happen to caller-owned output after a truncated record is rejected?

<details><summary>Reveal the worked answer</summary>

It must remain byte-for-byte unchanged; no partial checkpoint or decision is published.

</details>

## Primary research or standard

- [NISTIR 8202: Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

[Previous](443-use-the-existing-framework-record-chain-for-learning-provenance.md) | [Next](445-separate-ledger-events-from-model-training-and-evaluation.md) | [Course route](../../courses/llm-from-scratch/federated-audit-and-ledgers.html)

*Service to Many Leads to Greatness.*
