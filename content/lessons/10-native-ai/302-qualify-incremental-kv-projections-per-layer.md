# Lesson 302 — Qualify incremental K/V projections per layer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test qualify incremental k/v projections per layer within the bounded multi-layer Transformer.

## The underlying mechanism

A single new token passes through every Transformer layer. Its layer-specific K/V rows depend on that layer’s input state, which includes attention and residual calculations from previous layers. Reusing an incorrect upper-layer row can affect future logits even when the newest token appears correct.

## Step-by-step worked example

For three layers and eight channels, one proposed token yields `3 × 8 = 24` key scalars and 24 value scalars. Compare all 48 against the same token position in the canonical projection trace; do not aggregate layer outputs into one total before checking them.

## C23 implementation and Framework boundaries

The existing `UmiAiTrainingStackedKvStepPropose` returns `[layer][channel]` for new keys and values. A qualification service checks all new rows before the caller publishes them through `UmiAiTrainingStackedKvStoreAppend`.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

K/V shapes alone cannot prove projection equality. Check finite values and full elementwise numerical parity before committing a proposal.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** How many candidate K/V floats are inspected for four layers of width 16?

<details><summary>Reveal the worked answer</summary>

`2 × 4 × 16 = 128` values, covering keys and values.

</details>

## Mathematical connection

Read [Mathematics Unit 178](../11-maths-for-ai/178-count-layered-key-value-proposal-scalars.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](301-trace-canonical-key-and-value-projections.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
