# Lesson 154 — Plan a reproducible native inference performance experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

Performance is an observation about a particular system, compiler, input and model. It is not a property guaranteed by the words *cache*, *SIMD* or *parallel*. A useful native benchmark fixes model identity, token IDs, context policy, random seed and sampling parameters across both paths.

For a synthetic example, suppose one run produces 80 tokens in 2.8 seconds, and 0.3 seconds of that time was prompt prefill. Total throughput is `80 / 2.8 ≈ 28.57 tokens per second`, while a decode-only estimate is `80 / 2.5 = 32 tokens per second`. These two ratios answer different questions. The example is **not an actual Umicom measurement**.

Repeat warm-ups and measured trials, alternate the order of candidate and reference when possible, and report a distribution rather than the fastest run. Record the Windows build, CPU, compiler options and whether process CPU time or a monotonic wall clock was measured. Small toy decoders can be dominated by overhead.

## 2. Connect the lesson to Umicom Framework

`UmiAiTrainingStackedGenerationStats` reports workload counters, not elapsed time. For existing single-block prefix experiments, the Framework provides a separate `UmiAiTrainingPrefixBenchmarkRun` that qualifies numerical parity before interpreting timings. Do not transplant its speed conclusions to a stacked model without qualifying the same workload.

No generated model output should be compiled or executed during benchmarking. The experiment only compares numerical and byte outputs.

## 3. Practice

**Question:** Why is a lower token-layer row count insufficient to prove lower wall-clock latency?

<details><summary>Reveal the worked answer</summary>

Actual latency also depends on memory traffic, allocation, hardware utilisation, kernels and scheduling. Measure repeated comparable runs and first verify numerical parity.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
