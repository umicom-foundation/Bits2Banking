# Lesson 303 — Read back retained cache state after each append

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test read back retained cache state after each append within the bounded multi-layer Transformer.

## The underlying mechanism

An accepted append must preserve earlier cache rows and add exactly one new row in every layer. A single “append succeeded” status does not prove that the retained data was written correctly. Readback makes ownership mistakes and accidental overwrites observable.

## Step-by-step worked example

A two-layer cache with three retained tokens and eight channels contains `2 × 2 × 3 × 8 = 96` FP32 K/V values. After appending a fourth token it contains 128 values. A full readback compares every saved value, not only the latest 32.

## C23 implementation and Framework boundaries

Use `UmiAiTrainingStackedKvStoreRead` for each layer and position. Compare returned values with canonical projection tensors under the agreed tolerance. Keep the store opaque: tests must not inspect private pointer layouts.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A cache readback proves the store retained submitted values; it becomes a correctness argument only when the submitted rows were separately compared with the reference decoder.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** What does a successful readback prove that a successful append status alone does not?

<details><summary>Reveal the worked answer</summary>

It checks the actual retained scalar values and detects unintended changes to earlier rows.

</details>

## Mathematical connection

Read [Mathematics Unit 179](../11-maths-for-ai/179-count-complete-cache-readback-values.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](302-qualify-incremental-kv-projections-per-layer.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
