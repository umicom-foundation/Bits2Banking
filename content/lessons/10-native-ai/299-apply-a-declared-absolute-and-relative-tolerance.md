# Lesson 299 — Apply a declared absolute and relative tolerance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test apply a declared absolute and relative tolerance within the bounded multi-layer Transformer.

## The underlying mechanism

Floating-point reductions can disagree slightly because of accumulation order, conversion and architecture. A declared tolerance permits bounded numerical differences without treating all discrepancies as acceptable. It must be chosen independently of the observed test failure.

## Step-by-step worked example

For reference `1000.0`, candidate `1000.05`, absolute tolerance `0.001` and relative tolerance `0.0001`, the allowed difference is `0.001 + 0.0001 × 1000.05 = 0.101005`; the observed difference `0.05` qualifies. For reference `0`, candidate `0.002`, the allowance is `0.0010002`, so the comparison fails.

## C23 implementation and Framework boundaries

Use `UmiAiTrainingInferenceParityCompare` with FP32 arrays and finite nonnegative tolerances. The comparator reports mismatched element count, first mismatch and maximum deviations, leaving output unchanged when an argument is invalid.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A tolerance pass does not establish deterministic bitwise identity. Nonfinite values such as NaN and infinity must be rejected rather than incorrectly regarded as close.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** What happens when both tolerances are zero and two finite floats differ by one representable step?

<details><summary>Reveal the worked answer</summary>

The comparison reports a mismatch. Zero tolerance tests exact value equality (including +0 versus -0 as numerically equal).

</details>

## Mathematical connection

Read [Mathematics Unit 175](../11-maths-for-ai/175-count-unchanged-causal-prefix-checks.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](298-compare-entire-vocabulary-logit-vectors.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
