# LLM from Scratch — Lesson 425: Explain why a checksum cannot authenticate a learning worker

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Distinguish three assertions: bytes arrived unchanged, a holder of an approved key produced them, and a submitted weight update is mathematically useful.

## Concept and mechanism

An unkeyed digest is a public calculation. A malicious sender who edits a gradient vector can also recompute its SHA-256 checksum. An HMAC binds the message to secret key material, but only under the assumption that the sender alone possesses that key. Neither digest nor MAC establishes a lawful dataset, truthful FLOP count or lower validation loss.

## Guided reasoning

1. Write a claim table for integrity, authentication, authorisation and utility.
2. Separate the raw federated frame from its authenticated wrapper.
3. Require independently established worker-to-key mapping.
4. Reject model updates until their numeric and policy checks succeed.

## Worked example

An unauthorised actor changes a model delta from +0.05 to +5.0 and recomputes SHA-256. The recomputed digest can match the falsified data. Without the shared MAC key, the actor cannot feasibly create the HMAC tag for the new bytes.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A correct HMAC still does not prove that the sender performed training or that the delta improves the model.

## Test your understanding

**Question:** Can the coordinator accept a checksum-valid result as an authenticated training contribution? Why?

<details><summary>Reveal the worked answer</summary>

No. The hash is public and unkeyed. The coordinator needs a verified origin/key binding, explicit authorisation and separate numerical and held-out quality checks.

</details>

## Reading and source

- [RFC 2104, HMAC: Keyed-Hashing for Message Authentication](https://www.rfc-editor.org/rfc/rfc2104.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
