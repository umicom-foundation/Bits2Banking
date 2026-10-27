# AI Research Frontiers — Lesson 08: Low-level AI optimisation on x86, ARM and RISC-V

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Research foundations and practical systems comparisons

## What this topic investigates

C23 supplies a transparent numerical reference and shared API. Compiler optimisers, SIMD intrinsics, and approved Assembly kernels can target identified CPU hotspots on x86-64, ARM or RISC-V vector hardware. Real advantage depends on vector width, alignment, memory hierarchy, dtype and scheduling.

Distinguish a model architecture, an optimisation algorithm, an execution kernel and a dataset pipeline. Each operates at a different layer of the system and should be evaluated against its own fit-for-purpose baseline rather than combined into a single untestable claim.

## Worked example

A 64×64 by 64×64 dense matmul uses approximately 2×64³ = 524,288 arithmetic FLOPs under the common multiply-and-add counting convention. Execution time may be controlled by data movement, cache reuse and instruction selection; fewer source lines are not a benchmark.

## Practical research exercise

Build a scalar C23 reference, enable compiler vectorisation, test blocked tiling, then justify an architecture-specific kernel only after profiling. Compare full-vector numerical tolerances and energy at target quality with a known library baseline. Assembly is a *measured fast path*, not a replacement for portability.

For a reproducible result, fix the model/dataset revision, precision, hardware, source permissions and measurement conditions. Report both the primary metric and at least one limitation. The existing Umicom Framework owns reusable C23 maths, model interfaces, provenance and approval services; an application must reuse them rather than fork an equivalent implementation.

## Self-assessment

**Question:** What must stay constant when comparing a scalar kernel to a RISC-V vector implementation?

<details><summary>Reveal the explanation</summary>

Workload dimensions, data and precision contract, correctness target and the benchmarking environment must be declared; otherwise speed/energy claims are not comparable.

</details>

## Research starting points

- [FlashAttention — Dao et al. (2022)](https://arxiv.org/abs/2205.14135)
- [GaLore — Zhao et al. (2024)](https://arxiv.org/abs/2403.03507)

## Related courses

[Advanced native LLM research](../10-native-ai/390-study-c23-simd-riscv-kernels-with-controlled-baselines.md) · [Distributed Learning introduction](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
