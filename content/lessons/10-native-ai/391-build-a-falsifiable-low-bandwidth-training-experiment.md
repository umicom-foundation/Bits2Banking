# Lesson 391 — Design a falsifiable low-bandwidth research experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **design a falsifiable low-bandwidth research experiment**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A research comparison should pre-register a primary outcome and equal-resource baselines. Independent seeds, model and dataset hashes, train/evaluation split controls, network RTT/uplink caps, dropout scenarios and hardware identity must be captured. A convenient graph of training loss is not enough.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Plan 1-, 2- and 4-worker experiments; 10, 100 and 1,000 Mbps links; 5, 50 and 150 ms RTTs; and IID versus non-IID synthetic shards. Evaluate time to a fixed held-out loss, bytes transmitted, peak memory, energy where measured, rejected honest updates and accepted malicious updates. Report negative results.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Do not compare a 2-worker run consuming twice the training tokens with a 1-worker baseline and interpret the difference as a communication breakthrough. GeoMesh, DiLoCo and FedLoRA are existing prior art whose assumptions must be matched where feasible.

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

**Question:** Which pair of measurements should a study report if it claims an energy-efficient federation?

<details><summary>Reveal the worked answer</summary>

Measure time to the pre-registered quality threshold and joules consumed to that threshold, with actual power measurement methodology and matched training work.

</details>

## Mathematics companion

[Related Maths for AI Unit 243](../11-maths-for-ai/243-compare-hash-receipts-with-raw-tensors.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/)
- [DiLoCo — Douillard et al. (2023 preprint)](https://arxiv.org/abs/2311.08105)
- [Federated Low-Rank Adaptation Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
