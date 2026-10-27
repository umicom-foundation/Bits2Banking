# Lesson 380 — Understand non-IID client data and distribution shift

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **understand non-iid client data and distribution shift**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

In non-IID federated learning, each participant observes a different input distribution. A treasury desk, a programming tutor and a bank customer-support domain may produce gradients that legitimately disagree. Larger local datasets do not automatically imply higher-quality updates for every evaluation audience.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Suppose client A has 90% programming examples and 10% finance, while client B has 10% programming and 90% finance. Equal sample counts yield a balanced aggregate example distribution, but a held-out treasury evaluation may still get worse. Report per-domain outcomes and avoid assuming a weighted mean optimises fairness by construction.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

A globally lower aggregate loss can conceal a severe deterioration for a minority language or small institution. Personalisation and separate adapters can sometimes be more appropriate than one universal checkpoint.

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

**Question:** Why should a model card report both average performance and per-domain performance?

<details><summary>Reveal the worked answer</summary>

The mean conceals distribution-specific regressions. Per-domain evaluations reveal which participants or tasks deteriorate after aggregation.

</details>

## Mathematics companion

[Related Maths for AI Unit 235](../11-maths-for-ai/235-prove-the-lora-factor-averaging-counterexample.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Federated Low-Rank Adaptation Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)
- [SDFLoRA: Selective Decoupled Federated LoRA (IJCAI 2026)](https://ijcai.org/proceedings/2026/533)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
