# LLM from Scratch — Lesson 434: Distinguish retry safety from durable replay prevention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Separate already-implemented process-local job tickets from cross-restart duplicate handling.

## Concept and mechanism

The existing FederatedJob rejects a second completion for an already accepted process-local ticket. That gives a narrow idempotency boundary during one running coordinator round. It does not automatically survive a coordinator restart or prevent replay of an HMAC-valid message when its key epoch remains active. Durable inbox/outbox and correlation records must provide the stronger property.

## Guided reasoning

1. Authenticate and validate the complete frame.
2. Resolve public sequence to one admitted local job ticket.
3. Complete that ticket at most once.
4. Persist accepted result/correlation before acknowledging a remote worker.
5. Recover prior accepted IDs before accepting requests after restart.

## Worked example

A result for round 84, sequence 3 is accepted at 10:00 and the worker retries at 10:01. The live FederatedJob ticket rejects the second completion. If the coordinator restarts and loses its acceptance table, HMAC alone cannot detect the retry.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A timeout does not mean a worker did not finish; retries must not count extra samples or apply the delta twice.

## Test your understanding

**Question:** Does key rotation solve duplicate delivery within one key epoch?

<details><summary>Reveal the worked answer</summary>

No. Epoch checks only select authorised key material. Duplicate prevention requires a recorded round/sequence identity and a controlled acknowledgement/commit lifecycle.

</details>

## Reading and source

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
