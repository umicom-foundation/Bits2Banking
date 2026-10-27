# Lesson 310 — Separate numerical qualification from performance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test separate numerical qualification from performance within the bounded multi-layer Transformer.

## The underlying mechanism

The numerical release gate establishes that computations match the original semantics. A benchmark asks a different question: what latency and throughput does the qualified implementation achieve under controlled conditions?

## Step-by-step worked example

If a candidate executes 60 rather than 180 attention-query-layer rows but takes 5.3 ms rather than 4.8 ms, it is not faster on that workload. The extra costs might include store traversal and C23 tensor lifecycle overhead.

## C23 implementation and Framework boundaries

Run numerical qualification in Debug and under sanitizers. Once all relevant cases pass, use the existing native paired benchmark in a Release build with identical prompts, seeds and a stable environment. Preserve raw durations and the model identity.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

Do not compare candidate Release timings against reference Debug timings or infer a benefit from one favourable run.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Which of two results supports a speedup claim: fewer query rows or lower paired Release latency?

<details><summary>Reveal the worked answer</summary>

Lower paired Release latency under a controlled, reproducible workload supports a measured speedup for that workload. Query-row counts explain a potential mechanism.

</details>

## Mathematical connection

Read [Mathematics Unit 174](../11-maths-for-ai/174-count-active-prefix-vocabulary-logits.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](309-design-a-multilayer-context-qualification-matrix.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
