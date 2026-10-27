# Lesson 377 — Distributed learning versus inference scheduling

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **distributed learning versus inference scheduling**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A scheduler decides *when* an already trained decoder serves a token. A distributed learner decides *how* independent workers transform one **shared** parameter state using data, local gradients and a synchronisation rule. Existing Umicom KV sessions and the cooperative inference scheduler therefore cannot be renamed a federated trainer.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

An inference job outputs logits without changing weights. A learning round starts from theta_0, admits authorised worker updates delta_k, and proposes theta_1=theta_0+aggregate(delta_k). The proposal must be evaluated on data the contributors have not seen. Control-plane scheduling can be reused, but worker-data rights and model-update semantics demand a separate contract.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

If three workers generate 1,000 predictions but execute zero optimiser steps, there are three inference workloads and **zero training contributions**, regardless of total compute.

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

**Question:** Why should a bank-domain retrieval request not be treated as an update to training weights?

<details><summary>Reveal the worked answer</summary>

Retrieval and inference consume a model; training changes parameters. A bank-domain RAG request provides no authenticated gradient or authorised training example.

</details>

## Mathematics companion

[Related Maths for AI Unit 233](../11-maths-for-ai/233-calculate-a-three-worker-fedavg-update.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
