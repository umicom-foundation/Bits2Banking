# AI Research Frontiers — Lesson 03: Compare AdamW, Muon, SOAP and optimiser controls

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

AdamW is a reliable experimental control with adaptive moment estimates and decoupled weight decay. Muon uses matrix orthogonalisation for some parameter types, while SOAP studies matrix-aware preconditioning. Each method introduces different memory, arithmetic and tuning costs; reported speedups are conditional on the paper’s model and batch regime.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

If optimiser A takes 5,000 steps at 20 ms each, training time is 100 s. Optimiser B takes 4,000 steps at 30 ms, yielding 120 s. Fewer steps alone do not mean lower training time. This excludes data loading, evaluation, distributed communication and convergence-quality differences.

## Practical research exercise

Run a matched-compute and matched-time experiment with independent hyperparameter tuning. Hold dataset/seed/evaluation fixed and report time to target quality, optimiser-state memory and cross-domain tests; do not claim that one optimiser universally dominates.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Why should an optimiser be retuned when its batch size changes?

<details><summary>Reveal the explanation</summary>

Its effective noise scale, preconditioning behaviour and stable step-size range can change; an AdamW-tuned configuration is not automatically fair for another algorithm.

</details>

## Research starting points

- [Muon is Scalable for LLM Training (2025 preprint)](https://arxiv.org/abs/2502.16982)
- [SOAP: Improving and Stabilizing Shampoo using Adam (2024 preprint)](https://arxiv.org/abs/2409.11321)
- [The Best Optimizer Depends on Batch Size (October 2026 preprint)](https://arxiv.org/abs/2610.08975)

## Related courses

[Advanced native LLM research](../10-native-ai/383-aggregate-lora-updates-not-independent-factors.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
