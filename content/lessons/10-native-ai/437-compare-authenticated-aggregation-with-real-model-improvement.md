# LLM from Scratch — Lesson 437: Compare authenticated aggregation with real model improvement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Design an evaluation that does not mistake secure delivery for successful learning.

## Concept and mechanism

The FederatedRound service computes a weighted mean delta from compatible worker arrays. It must be evaluated against held-out data before model adoption. A secure channel prevents some message forgery, but cannot protect against a legitimately enrolled malicious contributor. A realistic experiment needs honest, stale, random, scaled and poisoned worker controls.

## Guided reasoning

1. Hold initial checkpoint and data partitions fixed.
2. Compare single-worker and FedAvg baselines at matched total tokens.
3. Run an authenticated contributor with a deliberately harmful but finite update.
4. Measure quality change and false-rejection rates.
5. Keep the MAC verification cost separate from model-evaluation compute.

## Worked example

Two legitimate workers return valid deltas 0.1 and -0.1 with equal sample counts. The mean delta is zero. All HMACs may be valid, yet no model update occurs and nothing has been learned from that particular aggregation result.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

Transport correctness is a prerequisite, not a substitute, for convergence and threat-model analysis.

## Test your understanding

**Question:** Can 100% successful HMAC checks support a claim of 100% useful learning?

<details><summary>Reveal the worked answer</summary>

No. A MAC checks message authenticity under a key. Useful learning requires independent validation of model quality, and adversarial insiders can produce correctly authenticated harmful updates.

</details>

## Reading and source

- [McMahan et al., Communication-Efficient Learning of Deep Networks from Decentralized Data](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Course study route](../../courses/llm-from-scratch/authenticated-federated-learning.html)

*Service to Many Leads to Greatness.*
