# Lesson 392 — Capstone: three-node native federated research

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **capstone: three-node native federated research**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

Build one small, auditable demonstration with three *logical* authorised workers. Produce their weight-space deltas externally to the aggregation component (synthetic values are sufficient for the first test), pin the same model hash, and use the Framework’s C23 weighted-round service. Explain exactly which responsibilities the component does—and does not—verify.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Use theta_0=1.000 and deltas +0.050, −0.010, +0.080 with sample counts 100, 250, 150. The candidate is 1.029. Next reject a duplicate contributor, mismatched base and oversized update without changing accepted state. Finally inspect the LoRA factor-averaging counterexample and design a held-out quality gate. Keep blockchain as a later, explicitly modelled alternative to signed records.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

Passing unit tests proves only the tested numerical and state-machine contracts; it does not prove that a malicious worker genuinely trained, that data was authorised, that secrets remain private or that model accuracy improved.

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

**Question:** What is the minimum evidence needed before describing this toy result as improved learning?

<details><summary>Reveal the worked answer</summary>

Actual controlled local training from the pinned base, authorised disjoint data, compatible updates, independent held-out evaluation and a comparison with a suitable non-federated baseline.

</details>

## Mathematics companion

[Related Maths for AI Unit 244](../11-maths-for-ai/244-evaluate-time-to-target-and-verification-overhead.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Federated Low-Rank Adaptation Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)
- [Proof of Learning (PoLe) — Lan et al. (2020)](https://arxiv.org/abs/2007.15145)
- [GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
