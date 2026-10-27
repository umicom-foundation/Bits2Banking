# AI Research Frontiers — Lesson 07: Design contamination-resistant and cost-aware evaluations

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

Training loss measures fit to the training objective, not necessarily end-user competence or safety. Evaluation must include held-out datasets, test contamination checks, domain fairness, malicious prompts and total resource cost.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

A coding assistant may pass 90/100 tests on code it has seen but only 55/100 on new repositories. Report both scores, their source/provenance and any test leakage. For banking use synthetic regulated-workflow fixtures, human-reviewed assertions and versioned API references; accuracy on general knowledge does not certify transaction correctness.

## Practical research exercise

Specify a primary target before tuning: e.g. held-out loss ≤ L with no regression in security tests and a 30-minute wall-clock cap. Record all attempts, including negative results, rather than selecting only the most favourable random seed.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Why is test-data leakage especially dangerous when studying federated fine-tuning?

<details><summary>Reveal the explanation</summary>

Worker data shards may contain near-duplicates of evaluation examples, making apparent generalisation an artefact of memorisation.

</details>

## Research starting points

- [DataComp-LM — controlled data curation](https://arxiv.org/abs/2406.11794)
- [FedAvg — McMahan et al. (AISTATS 2017)](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Related courses

[Advanced native LLM research](../10-native-ai/389-govern-multimodal-training-data-before-distribution.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
