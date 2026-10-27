# AI Research Frontiers — Lesson 06: Choose RAG, SFT, preference learning and verifiable rewards

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

RAG augments a model with external retrieved evidence while leaving weights unchanged. Supervised fine-tuning (SFT) changes response behaviour using approved examples. Direct Preference Optimisation (DPO) uses relative preference examples; reinforcement learning with verifiable rewards can train behaviours that a deterministic checker reliably scores.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

Suppose a Treasury Manual is updated today. Indexing the revised manual for RAG makes its cited facts available without retraining. A separately licensed SFT dataset might teach a tutor to explain bond valuation step by step. A compiler/test suite can evaluate generated code, but a persuasive response alone is not proof of executable correctness.

## Practical research exercise

Build separate evaluation suites: citation faithfulness and freshness for RAG, instruction following for SFT, preference validity for DPO, and execution-grounded reward checks for maths/code tasks. Never use private held-out answers as training prompts.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Can adding documents to a RAG index change a model’s parameter weights?

<details><summary>Reveal the explanation</summary>

Not by itself. Retrieval changes the information supplied during inference, not the trained parameter state.

</details>

## Research starting points

- [Direct Preference Optimization (2023)](https://arxiv.org/abs/2305.18290)
- [DeepSeekMath: GRPO and mathematical reasoning (2024)](https://arxiv.org/abs/2402.03300)
- [DataComp-LM — controlled data curation](https://arxiv.org/abs/2406.11794)

## Related courses

[Advanced native LLM research](../10-native-ai/389-govern-multimodal-training-data-before-distribution.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
