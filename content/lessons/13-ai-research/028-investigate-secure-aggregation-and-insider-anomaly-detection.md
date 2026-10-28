# AI Research Frontiers — Lesson 28: Investigate secure aggregation and insider anomaly detection

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

The privacy goal of hiding worker deltas can conflict with the security goal of inspecting each delta for poison or extreme norms.

## Concept and mechanism

Compare a trusted-enclave setting that inspects individual updates, a secure-sum setting that exposes only an aggregate, and protocols that selectively reveal challenge evidence. Report leakage, accuracy, attack acceptance and verification cost.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A hidden sum of three gradients may be finite even if one component is malicious; post-aggregation bounds need not identify the contributor.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** What design decision should be reported before claiming both worker privacy and full adversarial observability?

<details><summary>Reveal the worked answer</summary>

The exact information that each verifier can see and the trusted parties or proof assumptions that permit malicious-update checks.

</details>

## Reading and source

- [Bonawitz et al., Practical Secure Aggregation for Privacy-Preserving Machine Learning](https://arxiv.org/abs/1611.04482)

## Continue learning

[Course study route](../../courses/ai-research/trust-verification-research.html)

*Service to Many Leads to Greatness.*
