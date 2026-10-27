# Lesson 383 — Aggregate LoRA weight-space updates, not factors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **aggregate lora weight-space updates, not factors**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

A low-rank adaptation represents a dense update as Delta W = B × A. Each worker’s factors depend on its factorisation; the representation is not unique. Averaging B factors separately from A factors is generally **not** equivalent to averaging actual Delta W matrices.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

In a one-dimensional toy example, worker 1 returns B=+1,A=+1 and worker 2 returns B=-1,A=-1. Each has Delta W=+1. Averaging factors gives B_bar=0,A_bar=0, resulting in a false zero update. Averaging the **weight-space deltas** gives +1, as demonstrated by the C23 Framework test.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Full-delta aggregation may increase communication relative to shipping only small factors; low-rank recompression is a separate approximation needing numerical qualification. IJCAI 2025 FedLoRA and 2026 SDFLoRA document the significance of rank/client heterogeneity.

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

**Question:** Would averaging A and B work whenever they have compatible matrix dimensions?

<details><summary>Reveal the worked answer</summary>

No. Compatible shapes are necessary for arithmetic but do not remove the factorisation ambiguity. Aggregate actual weight-space effects or use a mathematically justified specialised method.

</details>

## Mathematics companion

[Related Maths for AI Unit 237](../11-maths-for-ai/237-calculate-dense-versus-low-rank-communication.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [LoRA — Hu et al. (2021)](https://arxiv.org/abs/2106.09685)
- [Federated Low-Rank Adaptation Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)
- [SDFLoRA: Selective Decoupled Federated LoRA (IJCAI 2026)](https://ijcai.org/proceedings/2026/533)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
