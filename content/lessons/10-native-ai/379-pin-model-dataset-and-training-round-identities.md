# Lesson 379 — Pin model, dataset and training-round identities

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **pin model, dataset and training-round identities**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A distributed update has meaning only relative to a specific base checkpoint, tokenizer and objective. Mixing an update derived from a different checkpoint into a current round is not interchangeable numerical work. The experiment also depends on dataset-shard rights and a reproducible training recipe.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Use an immutable job manifest containing a round identifier, checkpoint SHA-256, reviewed dataset commitment, algorithm, local-step budget, batch/sequence shape, seed and precision. Each contributor response repeats the base identity and carries its distinct worker identity. The native aggregation laboratory compares the externally supplied base digest; it does not authenticate that digest or verify the declared training run.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Two 32-byte SHA-256 values that happen to match identify the same declared bytes under collision-resistance assumptions. They do not demonstrate that a dataset was authorised, that weights were trained honestly or that a signer is trusted.

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

**Question:** Which two independent checks must happen before a checkpoint-digest match can be treated as reliable authorisation?

<details><summary>Reveal the worked answer</summary>

Verify the digest against the actual immutable checkpoint and authenticate the worker/job through the existing Framework identity/approval layer; separately review data rights.

</details>

## Mathematics companion

[Related Maths for AI Unit 234](../11-maths-for-ai/234-compare-unweighted-and-sample-weighted-averages.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Practical Secure Aggregation — Bonawitz et al. (CCS 2017)](https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
