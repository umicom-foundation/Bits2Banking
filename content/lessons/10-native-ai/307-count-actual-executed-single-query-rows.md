# Lesson 307 — Count actual executed single-query rows

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test count actual executed single-query rows within the bounded multi-layer Transformer.

## The underlying mechanism

Optimising one attention query does not remove key/value reads, normalisation, MLP work, allocations, or canonical rollover forwards. Work accounting must distinguish executed query rows from projected token-layer rows and full-context forward rows.

## Step-by-step worked example

With three layers and a five-token visible prefix, a one-query-per-layer append executes three query-layer rows. The historical placeholder-query method executed `3 × 5 = 15`. This arithmetic expresses a change in one type of work, not a fivefold decrease in wall-clock time.

## C23 implementation and Framework boundaries

Compare the existing `UmiAiTrainingStackedKvStepReport` counters against the accepted cache transition and the independent full-context reference. Keep measured elapsed time in the separate Framework benchmark service.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

An operation count does not measure memory bandwidth, allocator overhead, CPU frequency, cache misses or scheduler delays. Never transform the query-row ratio directly into a speedup claim.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** A three-layer decoder makes two growing-prefix appends. How many single-query-layer rows are executed?

<details><summary>Reveal the worked answer</summary>

`3 × 2 = 6` query-layer rows, excluding prefill and full-window rebuilds.

</details>

## Mathematical connection

Read [Mathematics Unit 183](../11-maths-for-ai/183-interpret-small-paired-latency-samples.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](306-keep-evidence-failure-atomic.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
