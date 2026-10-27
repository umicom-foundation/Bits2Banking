# AI Research Frontiers — Lesson 016: Benchmark C23 SIMD and RISC-V learning kernels

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

Low-level optimisation must preserve a scalar numerical oracle and report compiler flags, dtype, hardware, vector width, memory hierarchy and energy. Assembly and RISC-V Vector operations are useful *after* profiling establishes bottlenecks. Avoid a new tensor implementation where Framework already owns the operation; use an optional optimised backend with independent parity tests.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

Compare scalar C23 matrix multiplication against compiler auto-vectorisation and, if hardware supports it, one bounded SIMD path on identical shapes. Record max absolute/relative error and median wall-clock per warm workload. Include model-level latency to avoid mistaking a micro-kernel gain for a total training improvement.

## Falsifiable hypothesis and measurements

Hypothesis: a specific architecture-targeted kernel reduces time or joules for fixed matrix shapes without exceeding declared numerical error; report negative results and fallbacks.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [RISC-V International](https://riscv.org/)
- [GaLore — Memory-Efficient LLM Training by Gradient Low-Rank Projection](https://arxiv.org/abs/2403.03507)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
