# Lesson 381 — Compare local SGD, DiLoCo and synchronisation cadence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **compare local sgd, diloco and synchronisation cadence**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

Every synchronisation round exchanges information over a network. Local SGD permits multiple local optimiser steps before a shared update. DiLoCo studies a particularly low-communication outer optimisation regime across weakly connected accelerator islands.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

At 100 local steps per communication round, a 10,000-step worker needs roughly 100 update exchanges rather than one per step. That is 100× fewer exchanges in the idealised count, but the model may drift and the exchanged payload may differ. Latency, uplink throughput and the quality target determine whether the change is beneficial.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

The DiLoCo paper reports gains under its studied model/data/network conditions. It does not establish that increasing local steps always improves convergence or that all workers are equally trustworthy.

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

**Question:** Which two experimental measurements reveal whether fewer synchronisations are worthwhile?

<details><summary>Reveal the worked answer</summary>

Measure actual bytes transferred and wall-clock time to reach a pre-specified held-out quality target, against a strong baseline at matched training compute.

</details>

## Mathematics companion

[Related Maths for AI Unit 236](../11-maths-for-ai/236-count-lora-trainable-parameters-and-bytes.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)
- [OpenDiLoCo — Jaghouar et al. (2024)](https://arxiv.org/abs/2407.07852)
- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
