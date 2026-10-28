# Distributed Learning — Lesson 37: Explain shared-secret worker authentication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

HMAC authenticates bytes only in relation to enrolled key possession. A real worker identity requires the registry to bind key material to a uniquely authorised worker and dataset policy.

## Concept and mechanism

A worker is assigned a shard and uses its privately provisioned secret to authenticate the resulting frame. A second worker must not copy or reuse that secret. The coordinator binds the key epoch, worker ID and declared dataset permission before accepting the update.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A group secret shared by five peers permits any holder to impersonate any other holder. Per-worker credentials reduce that ambiguity but cannot prevent key theft.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** What does the MAC actually prove about the worker?

<details><summary>Reveal the worked answer</summary>

Someone possessing the key authenticated these bytes; it does not independently prove which person executed training or that training happened.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
