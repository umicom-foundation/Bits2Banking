# Distributed Learning — Lesson 43: Treat expired assignments and revoked workers as distinct failures

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

An expired job and a revoked key are different reasons to reject a message. Both must fail closed without changing the aggregation state.

## Concept and mechanism

First authenticate the frame using a currently authorised worker key; then check whether the ticket remains admitted and within its policy window; finally validate numeric and rights conditions. A cancelled ticket must not be reopened by a valid MAC.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A result produced just before its deadline might arrive after cancellation. It cannot override the coordinator’s authoritative cancellation state.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** Can a successfully authenticated frame automatically reactivate a cancelled assignment?

<details><summary>Reveal the worked answer</summary>

No. Authentication never changes the job-owner lifecycle state.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
