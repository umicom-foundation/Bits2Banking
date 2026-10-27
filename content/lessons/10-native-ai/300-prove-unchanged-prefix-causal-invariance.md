# Lesson 300 — Prove unchanged-prefix causal invariance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test prove unchanged-prefix causal invariance within the bounded multi-layer Transformer.

## The underlying mechanism

A causal decoder must not allow future token values to alter earlier positions. Learned absolute position embeddings make row indices significant; preserving position indices while adding a suffix should therefore preserve the earlier logits, apart from numerical tolerance.

## Step-by-step worked example

With context six, compare `[A,B,BOS,BOS,BOS,BOS]` to `[A,B,C,BOS,BOS,BOS]`. Logit rows zero and one should agree across the two evaluations. The row for `C` may differ because that position was previously occupied by padding.

## C23 implementation and Framework boundaries

The qualification service snapshots the previous full-trace logits and compares exactly `oldPrefixLength × vocabularySize` scalars after every append. It does not apply this check across position rollover, which changes the positions of surviving tokens.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A causal-invariance test should use two distinct future suffixes and compare unchanged prefixes. Equal sampled token IDs alone cannot establish this property.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** For an unchanged prefix of four tokens in a 260-token model, how many logit values are inspected after appending one token?

<details><summary>Reveal the worked answer</summary>

`4 × 260 = 1,040` scalar comparisons.

</details>

## Mathematical connection

Read [Mathematics Unit 176](../11-maths-for-ai/176-calculate-layer-major-kv-scalar-offsets.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](299-apply-a-declared-absolute-and-relative-tolerance.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
