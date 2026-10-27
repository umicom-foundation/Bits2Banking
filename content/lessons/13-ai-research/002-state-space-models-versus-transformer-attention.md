# AI Research Frontiers — Lesson 02: State-space sequence mixers versus Transformer attention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

Transformer attention compares queries with keys from context; state-space models use learned recurrent state transitions to capture history. Mamba introduced selective state-space updates as a different way to scale long-sequence processing. Hybrid designs combine attention and state-space operations when both exact retrieval and efficient recurrence matter.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

Suppose attention processes a prompt of N=1,024 tokens. A dense query-key score matrix has N²=1,048,576 positions per head in a full forward pass. A linear-scan state-space operator need not materialise this N×N matrix, but it introduces its own state and numerical kernels. This is a complexity comparison, not a quality or hardware-speed benchmark.

## Practical research exercise

Measure actual prefill latency, held-out perplexity, retrieval accuracy on long-range tasks and memory traffic. The Framework’s current tiny native decoder uses attention; state-space training is a **proposed research direction**, not a merged Umicom backend.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** Does eliminating the N×N score matrix ensure a state-space model memorises long-range facts equally well?

<details><summary>Reveal the explanation</summary>

No. Efficiency and representation capacity are different properties, and exact retrieval tasks may favour different architectures.

</details>

## Research starting points

- [Mamba — Gu & Dao (2023)](https://arxiv.org/abs/2312.00752)
- [FlashAttention — Dao et al. (2022)](https://arxiv.org/abs/2205.14135)

## Related courses

[Advanced native LLM research](../10-native-ai/390-study-c23-simd-riscv-kernels-with-controlled-baselines.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
