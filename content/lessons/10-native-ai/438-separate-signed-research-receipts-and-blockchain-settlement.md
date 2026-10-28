# LLM from Scratch — Lesson 438: Separate signed research receipts and blockchain settlement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Explain why HMAC, signatures, append-only logs and consensus establish different claims.

## Concept and mechanism

An HMAC is shared-key authentication and does not provide public non-repudiation: the receiver also knows the secret. Detached signatures can bind a public-key identity to a statement. An append-only hash-linked log supports local tamper evidence. Blockchain consensus is a further coordination mechanism across independent administrators and does not magically validate training computations.

## Guided reasoning

1. Produce one canonical job/update receipt.
2. Identify which fields may safely be public.
3. Decide whether a shared-key MAC or independent signature fits the trust model.
4. Compare a signed audit log against a multi-party ledger baseline.
5. Keep weights, gradients and private datasets off-chain.

## Worked example

A public receipt might list the base checkpoint digest, round, accepted outcome and policy version. It should not include a raw customer transaction used during local fine-tuning or the shared HMAC key.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

A signed receipt can be truthful or false about training. Verification and challenge evidence must be separately evaluated.

## Test your understanding

**Question:** Why is an HMAC-authenticated frame unsuitable as a publicly independently verifiable contribution receipt?

<details><summary>Reveal the worked answer</summary>

A verifier lacking the secret cannot check it. Giving verifiers the secret allows them to forge tags. A separate signature/attestation scheme with explicit trust policies is required for public verification.

</details>

## Reading and source

- [SoK: Blockchain-based Decentralized AI](https://arxiv.org/abs/2411.17461)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
