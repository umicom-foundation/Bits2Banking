# Distributed Learning — Lesson 42: Handle retries without duplicating samples

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

A network retry should not reapply an already accepted update, even when the original acknowledgement was lost.

## Concept and mechanism

The coordinator maps each public round/sequence to one process-local FederatedJob ticket. Completing the ticket closes it; another completion is rejected. Cross-restart deduplication requires durable inbox/outbox storage before acknowledging acceptance.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

Worker B’s message arrives three times after packet loss; its sample count must be included once.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** If the coordinator has no durable acceptance log after restarting, does verifying the MAC prevent a replay?

<details><summary>Reveal the worked answer</summary>

No. The same valid signed or MAC-protected bytes can be replayed. Persistent correlation state is needed.

</details>

## Reading and source

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Course study route](../../courses/distributed-learning/worker-authentication-and-replay.html)

*Service to Many Leads to Greatness.*
