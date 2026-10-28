# LLM from Scratch — Lesson 440: Build a reproducible authenticated federated inference-to-training capstone

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Assemble a bounded evidence table linking authenticated messages, immutable job identities and numerical aggregation.

## Concept and mechanism

A useful capstone has two stages: first verify that the native HMAC wrapper reproduces published cryptographic vectors and rejects corrupted inputs without side effects; second feed verified, authorised synthetic deltas into the existing FederatedJob/FederatedRound to demonstrate exact-once process-local submission and weighted aggregation. Then explain all missing capabilities for real federated model training.

## Guided reasoning

1. Use a pinned SHA-256 implementation and RFC test vectors.
2. Fix one synthetic per-worker secret and one model-checkpoint digest.
3. Test wrong-key, wrong-epoch, malformed and duplicate submissions.
4. Run GCC, Clang and sanitizers.
5. Record everything still untested: live network, identity enrolment, durable replay, model training and independent quality.

## Worked example

For one worker with two delta coordinates (0.25, -0.125), one accepted ticket produces exactly those coordinates after finalisation. The second completion for the same ticket must fail without adding its sample count again.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A complete classroom test is not a production security audit, licence grant, authenticated LAN result or proof of model convergence.

## Test your understanding

**Question:** What four independent classes of evidence should a final research receipt distinguish?

<details><summary>Reveal the worked answer</summary>

Cryptographic/wire correctness, worker and dataset authorisation, numerical/aggregation correctness, and independent held-out model quality (with performance measured separately).

</details>

## Reading and source

- [RFC 4231, HMAC-SHA-256 test vectors](https://www.rfc-editor.org/rfc/rfc4231.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
