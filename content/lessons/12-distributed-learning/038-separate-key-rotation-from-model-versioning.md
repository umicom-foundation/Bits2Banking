# Distributed Learning — Lesson 38: Separate key rotation from model versioning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Cryptographic epoch rotation and model checkpoint updates are independent lifecycle events. Binding both into a receipt makes changes auditable without treating them as equivalent.

## Concept and mechanism

A worker may keep using the same checkpoint while the coordinator rotates its transport secret. The update still needs exact matching to the pinned base checkpoint; the new key does not relax that constraint.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

Epoch 5 is no longer approved, but an inner frame still contains the correct model hash. Authentication must reject it before numerical aggregation.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** Does a current checkpoint make an expired key valid?

<details><summary>Reveal the worked answer</summary>

No. Model identity and key validity are different checks.

</details>

## Reading and source

- [RFC 5869, HMAC-based Extract-and-Expand Key Derivation Function](https://www.rfc-editor.org/rfc/rfc5869.html)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
