# AI Research Frontiers — Lesson 01: Sparse Mixture-of-Experts and expert routing

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

Mixture-of-Experts (MoE) models route each token to a subset of expert feed-forward networks. This can increase the number of stored parameters without proportionally increasing per-token computation, but the network may need to dispatch activations across devices and coordinate load balancing.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

Consider eight experts and top-two routing. A token activates two of eight expert modules (25% of that collection) but still uses shared dense layers, the router and attention. The statement **does not** mean the model executes only 25% of its total FLOPs, uses 25% of memory, or becomes 4× faster.

## Practical research exercise

Design a controlled comparison: dense FFN versus top-two expert FFN at fixed data and target quality. Record expert load skew, all-to-all bytes, per-token latency and peak device memory. At WAN scale, routing individual token activations across slow links may erase sparse-compute savings.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** If all tokens route to the same expert, what happens to the idealised parallelism?

<details><summary>Reveal the explanation</summary>

That expert becomes overloaded while others sit idle; a routing/load-balancing objective and sufficient network bandwidth are required.

</details>

## Research starting points

- [DeepSeek-V3 Technical Report — MoE and MLA](https://arxiv.org/abs/2412.19437)

## Related courses

[Advanced native LLM research](../10-native-ai/390-study-c23-simd-riscv-kernels-with-controlled-baselines.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
