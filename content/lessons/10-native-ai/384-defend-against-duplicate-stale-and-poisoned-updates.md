# Lesson 384 — Distinguish duplicate, stale and poisoned updates

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **distinguish duplicate, stale and poisoned updates**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A coordinator must not mistake superficial input checks for Byzantine robustness. Duplicate contributor IDs, mismatched base snapshots, NaNs and excessive update norms can be rejected deterministically. A carefully crafted poisoned update can nevertheless satisfy every one of these checks.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

For an update vector (3,4), the L2 norm is 5. A declared maximum 4 should reject it before aggregation. The C23 round validator uses a bounded L2 check. A malicious worker submitting (0.1,0.1) with a harmful direction may pass; an independent quality evaluation and a stated adversary model are still needed.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Cryptographic hashes are commitments to bytes, not a model-utility oracle. Nor is a sample count certified simply because the worker includes it in a request.

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

**Question:** What is the exact difference between a numerical bounds check and a poisoning defence?

<details><summary>Reveal the worked answer</summary>

A bound check rejects an explicit numeric condition. Poisoning defence attempts to identify harmful learning behaviour and requires threat-specific evidence beyond shape/norm validation.

</details>

## Mathematics companion

[Related Maths for AI Unit 238](../11-maths-for-ai/238-quantify-non-iid-client-mixtures.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Practical Secure Aggregation — Bonawitz et al. (CCS 2017)](https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/)
- [Proof of Learning (PoLe) — Lan et al. (2020)](https://arxiv.org/abs/2007.15145)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
