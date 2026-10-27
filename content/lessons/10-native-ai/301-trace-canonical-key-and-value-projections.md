# Lesson 301 — Trace canonical key and value projections

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test trace canonical key and value projections within the bounded multi-layer Transformer.

## The underlying mechanism

The KV store cannot independently prove that the rows it receives are projections of the original Transformer. The source of that evidence is the canonical decoder’s projection trace, which observes its existing matrix operations without substituting a new attention algorithm.

## Step-by-step worked example

For three layers, context six and channel width eight, each complete K or V trace has `3 × 6 × 8 = 144` FP32 elements. The flat scalar offset of layer two (zero based), row four, channel three is `(2 × 6 + 4) × 8 + 3 = 131`.

## C23 implementation and Framework boundaries

Use `UmiAiTrainingStackedDecoderTraceProjections`. Its K/V layout is `[layer][context position][channel]`, whereas prefill requests `[layer][retained prefix position][channel]`; the stride changes when the prompt is shorter than context.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

Copy compact per-layer segments before prefill. A plain memcpy of the first `layers × retained × width` scalars would mix layers unless the prompt already occupies the full context.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Why must a two-token prefix be compacted separately for each layer before cache prefill?

<details><summary>Reveal the worked answer</summary>

The canonical source trace uses a full-context stride for each layer, while the prefill store expects only the provided prefix rows per layer.

</details>

## Mathematical connection

Read [Mathematics Unit 177](../11-maths-for-ai/177-count-proposed-vocabulary-logits.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](300-prove-unchanged-prefix-causal-invariance.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
