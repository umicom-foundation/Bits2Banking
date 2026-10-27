# Lesson 312 — Complete the canonical inference acceptance matrix

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test complete the canonical inference acceptance matrix within the bounded multi-layer Transformer.

## The underlying mechanism

A usable acceptance matrix connects checkpoint identity, exact test inputs, canonical logits, incremental proposals, KV readback, causal invariance, rollover and sampling. A result should make omissions explicit instead of merging all evidence into a single pass/fail headline.

## Step-by-step worked example

Consider a context-six, two-layer model with a two-token prefix and eight fixed continuation tokens. It performs four growing-prefix transitions and four full-window replacements. The new C23 diagnostic checks every active canonical row, four candidate logit vectors, four sets of K/V proposals, and the stored rows after all transitions.

## C23 implementation and Framework boundaries

Run `UmiAiTrainingStackedInferenceQualify`, inspect its comparison counts, and separately run seeded canonical versus incremental generation and the paired benchmark. Report numerical acceptance independently of measured latency. No release claim is justified until the real Framework checkout and representative hardware have been qualified.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

The educational model is bounded and uses learned absolute positions. Its acceptance results must not be extrapolated to large GPU inference engines or to different attention/position policies.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Which three categories of evidence belong in the final release record?

<details><summary>Reveal the worked answer</summary>

Numerical semantics (all relevant logits and K/V), state/lifecycle behaviour (identity, rollover and failure atomicity), and measured runtime evidence (paired latency and resource costs).

</details>

## Mathematical connection

Read [Mathematics Unit 176](../11-maths-for-ai/176-calculate-layer-major-kv-scalar-offsets.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](311-run-inference-checks-through-native-framework-tools.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
