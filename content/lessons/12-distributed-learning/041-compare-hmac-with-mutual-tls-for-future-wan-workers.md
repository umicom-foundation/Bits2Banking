# Distributed Learning — Lesson 41: Compare HMAC with mutual TLS for future WAN workers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

HMAC authenticates an application payload under a shared secret. Transport protocols such as TLS 1.3 provide secure channels, and mutual authentication adds independently checked peer credentials.

## Concept and mechanism

An authenticated UMFA frame can ride inside an authenticated transport, but cannot replace confidentiality of a raw gradient. The transport and payload serve different boundaries, and key management must avoid one shared group secret across every worker.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

HMAC-only file exchange can detect changes but exposes plaintext model updates to observers with filesystem or network access.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** Does HMAC encrypt the weight delta?

<details><summary>Reveal the worked answer</summary>

No. It provides keyed integrity only; confidentiality needs an approved encrypted channel or encryption scheme.

</details>

## Reading and source

- [RFC 9846, TLS 1.3 (2026 revision)](https://www.rfc-editor.org/rfc/rfc9846.html)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
