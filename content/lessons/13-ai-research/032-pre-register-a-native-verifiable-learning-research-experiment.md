# AI Research Frontiers — Lesson 32: Pre-register a native verifiable-learning research experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** UK English · **Native implementation:** C23/Assembly where technically justified

## Learning outcome

Research validity depends on controlling baselines, data rights, compute budgets and independent held-out evaluation before seeing favourable results.

## Concept and mechanism

Define a primary metric (e.g. time to a target held-out loss), worker and WAN settings, adversary rate, verification mode and test seeds. Compare native Framework results with established FedAvg and DiLoCo baselines; report negative results and confidence intervals.

## Guided reasoning

1. Identify the relevant identity, data or model boundary.
2. State the attacker and failure assumptions.
3. Describe an independent check rather than accepting a self-reported value.
4. Record what the experiment would fail to establish.

## Worked example

A system that lowers network bytes but worsens validation loss under equal compute is not an unequivocal training improvement.

## How this connects to a native software system

The authoritative AI, identity, messaging, cryptographic and numeric contracts belong in **Umicom Framework**. Applications such as Umicom LLM, Studio, RAG and Education consume those capabilities through established APIs, rather than implementing independent maths, secret stores or message parsers. Where a specialised feature is not present, it is an explicitly scoped research or future-development topic—not a claim that all components exist today.

## Correctness and research boundary

The worked example is synthetic. It is a study of trade-offs and security claims; the existence of a standard or research paper does not establish that every described network or model service is implemented in Umicom Framework.

## Test your understanding

**Question:** What prevents a system from claiming progress by selectively showing only the fastest run?

<details><summary>Reveal the worked answer</summary>

Pre-registered endpoints, repeated seeds, matched budgets and publication of complete result distributions including failures.

</details>

## Reading and source

- [Douillard et al., Distributed Low-Communication Training of Language Models](https://arxiv.org/abs/2311.08105)

## Continue learning

[Course study route](../../courses/ai-research/trust-verification-research.html)

*Service to Many Leads to Greatness.*
