# Lesson 386 — Separate identity, execution and useful learning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **separate identity, execution and useful learning**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A credible verification statement names three different questions: (1) Are the claimed input/output bytes the ones referenced? (2) Did the worker perform the prescribed computation? (3) Is the resulting model better under independent evaluation? One answer does not prove the others.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

A valid SHA-256 commitment can establish that an uploaded update matches a recorded byte sequence; it cannot demonstrate the worker trained it. Selective replay can check part of a stochastic execution, but the verifier may spend substantial compute and encounter floating-point nondeterminism. A hold-out dataset can measure useful quality, but a single score is not a proof of honestly performed training.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Statements like “cryptographically verified high-quality training” need a precise cryptographic proof model and separately measured quality criteria. In this course, the native round service certifies only arithmetic admissibility and deterministic aggregation.

For any proposed optimiser or security improvement, retain a simple controlled baseline. A negative result is still a meaningful research observation when measured under declared conditions.

## Native C23 engineering connection

The Framework remains the authority for model mathematics, checkpoints, messaging and validation. The opt-in `UmiAiTrainingFederatedRound` component delivered with this course accepts compatible **weight-space deltas**, performs bounded sample-weighted accumulation and rejects malformed/duplicate contributions. It is **not** a remote trainer, privacy protocol, cryptographic verifier or blockchain. The `labs/native/distributed-learning/fedavg-round` program exercises the actual Framework API rather than copying the aggregator into the educational application.

A completed advanced implementation would connect locally trained deltas, verified identities, authorised datasets and held-out evaluation through the existing Framework services. New public release claims require independent qualification and not just a passing demonstration.

## Research method and suggested experiment

1. State one hypothesis that could be disproved and identify the exact baseline.
2. Pin one model/checkpoint identity, one reviewed dataset partition and an explicit seed.
3. Define what is observed: loss, bytes, elapsed time, memory, energy or verification rejection counts.
4. Try a success case and at least one deliberately malformed or harmful input.
5. Record the distinction between *observed*, *simulated* and *not tested* results.

## Exercise

**Question:** A signed update has a correct base checkpoint hash but worsens the held-out loss. Which verification claim has failed?

<details><summary>Reveal the worked answer</summary>

The useful-quality claim has failed under that evaluation; the identity and authorship claims might still hold.

</details>

## Mathematics companion

[Related Maths for AI Unit 239](../11-maths-for-ai/239-compute-wan-transfer-and-rtt-lower-bounds.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [Proof of Learning (PoLe) — Lan et al. (2020)](https://arxiv.org/abs/2007.15145)
- [Proof-of-Learning with Incentive Security (2024 preprint)](https://arxiv.org/abs/2404.09005)
- [INTELLECT-2 — globally distributed RL (2025 preprint)](https://arxiv.org/abs/2505.07291)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
