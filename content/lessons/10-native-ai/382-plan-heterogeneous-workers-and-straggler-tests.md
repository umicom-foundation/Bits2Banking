# Lesson 382 — Plan heterogeneous workers and straggler experiments

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **plan heterogeneous workers and straggler experiments**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

Distributed training across consumer CPUs, RISC-V devices and powerful GPUs exposes unequal memory, throughput, uptime and network links. A fast worker can idle while waiting for a slower member of a synchronous round; an asynchronous worker can return stale updates.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Compare nodes taking 20 s, 50 s and 90 s for the same local budget. A synchronous round cannot finish sooner than the 90 s worker, ignoring network overhead. Reassigning work proportional to capacity may reduce idle time, but sample/data quality and local-step validity must remain controlled.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

GeoMesh (Findings EMNLP 2026) studies workload balancing and compressed update exchange. Its reported improvements are author experiments; a Umicom experiment must compare time-to-target perplexity and energy on specified hardware rather than importing the paper’s percentages.

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

**Question:** Why can reducing the slowest worker’s assignment harm the experiment if sample weights are ignored?

<details><summary>Reveal the worked answer</summary>

It changes the effective training mixture and aggregate contribution weights, which may shift validation quality despite better utilisation.

</details>

## Mathematics companion

[Related Maths for AI Unit 236](../11-maths-for-ai/236-count-lora-trainable-parameters-and-bytes.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/)
- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
