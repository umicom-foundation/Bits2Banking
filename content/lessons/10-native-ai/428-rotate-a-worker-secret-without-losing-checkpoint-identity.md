# LLM from Scratch — Lesson 428: Rotate a worker secret without losing checkpoint identity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Differentiate an authentication-key epoch from the model checkpoint identifier and the training round.

## Concept and mechanism

A key epoch names which approved secret should authenticate a message. It is a public label rather than the secret itself. A model checkpoint digest names the bytes of the base model; a training round groups compatible assignments. A successful key rotation should not silently authorise a new dataset or convert a stale model update into a valid one.

## Guided reasoning

1. Bind secrets to individual enrolled workers.
2. Record which epochs are permitted.
3. Authenticate the epoch and payload together.
4. Refuse unexpected epochs.
5. Retire compromised keys and log that revocation with governed access.

## Worked example

Worker W uses epoch 5 while its coordinator expects epoch 6. Even when the inner wire checksum is correct, the authenticated envelope should be rejected. The base checkpoint hash might still be unchanged; that does not override the epoch rejection.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

An epoch number cannot stop replay on its own. A previously valid message at the same epoch can still be resent.

## Test your understanding

**Question:** Does changing a key epoch require retraining the model? Explain the boundary.

<details><summary>Reveal the worked answer</summary>

No. Key rotation changes the transport/authentication trust material. Checkpoint identity and model weights remain independent unless a governance policy deliberately couples their release.

</details>

## Reading and source

- [RFC 5869, HMAC-based Extract-and-Expand Key Derivation Function](https://www.rfc-editor.org/rfc/rfc5869.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
