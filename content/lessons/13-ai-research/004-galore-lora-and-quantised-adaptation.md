# AI Research Frontiers — Lesson 04: Distinguish GaLore, LoRA and quantised adaptation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

LoRA freezes the base matrix and learns low-rank adapter factors. QLoRA commonly stores the frozen base in quantised form while training adapters in suitable arithmetic precision. GaLore projects gradients into a low-rank subspace to reduce optimiser-state burden while enabling broader model-weight updates.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

A frozen dense projection of 4096×4096 has 16,777,216 scalars; rank-eight LoRA factors contain 65,536 trainable scalars. Ratio 256 relates to **one projection’s trainable values** and not the total model RAM, full dataset cost or inference acceleration.

## Practical research exercise

Compare each method at fixed held-out quality under a declared accelerator-memory ceiling. Record trainable elements, optimiser bytes, actual peak memory, checkpoint traffic and inference compatibility. A production design should reuse Framework’s existing native low-rank and optimiser modules rather than duplicating them.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Does QLoRA’s four-bit storage guarantee four-bit backpropagation arithmetic?

<details><summary>Reveal the explanation</summary>

No. Quantised base storage is not the same as performing every computation in that low precision.

</details>

## Research starting points

- [LoRA — Hu et al. (2021)](https://arxiv.org/abs/2106.09685)
- [QLoRA — Dettmers et al. (2023)](https://arxiv.org/abs/2305.14314)
- [GaLore — Zhao et al. (2024)](https://arxiv.org/abs/2403.03507)

## Related courses

[Advanced native LLM research](../10-native-ai/383-aggregate-lora-updates-not-independent-factors.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
