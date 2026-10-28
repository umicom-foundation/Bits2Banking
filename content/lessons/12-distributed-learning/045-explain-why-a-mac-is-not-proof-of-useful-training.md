# Distributed Learning — Lesson 45: Explain why a MAC is not proof of useful training

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Cryptography can validate declared bytes but cannot certify that the model improved. Experimental utility requires an independent held-out metric.

## Concept and mechanism

A worker with valid credentials can submit random FP32 values inside the norm bound. The HMAC will still verify. The coordinator needs baseline and candidate quality comparisons at matched compute, with poisoning controls and transparent acceptance thresholds.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A weighted mean update of zero from two opposite valid deltas is an authenticated numerical result, not a demonstrated model improvement.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** Can one signed evaluation receipt prove the worker computed its claimed gradient?

<details><summary>Reveal the worked answer</summary>

Not without an independently justified execution proof or challenge protocol and a clearly stated threat model.

</details>

## Reading and source

- [Proof of Learning: An Incentive-Compatible Blockchain Consensus Mechanism](https://arxiv.org/abs/2007.15145)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
