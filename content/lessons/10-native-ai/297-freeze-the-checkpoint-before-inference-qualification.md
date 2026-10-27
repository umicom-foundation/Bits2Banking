# Lesson 297 — Freeze the checkpoint before inference qualification

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test freeze the checkpoint before inference qualification within the bounded multi-layer Transformer.

## The underlying mechanism

A numerical comparison is meaningful only if both execution paths read the same model parameters. A vocabulary logit changes when a weight changes, even if the query, input tokens and attention code do not. A checkpoint identity therefore belongs to the experiment definition alongside context length, attention heads and token IDs.

## Step-by-step worked example

Suppose two candidate runs both use a context length of six and two Transformer layers, but the second run has undergone one SGD update. The shape still matches, yet its logits are not required to match the previous checkpoint. A model-identity digest distinguishes those runs; it cannot prove who published the weights.

## C23 implementation and Framework boundaries

Use the existing `UmiAiTrainingStackedModelIdentityCapture` and `UmiAiTrainingStackedModelIdentityVerify` services before comparing results. Keep a borrowed model alive and caller-serialised throughout qualification; no application-local checkpoint implementation is needed.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A SHA-256 match is content identity, not a signature or authorisation decision. Refuse a mutated checkpoint and do not silently relax the tolerance to hide it.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Why should a model identity be captured even if model dimensions have not changed?

<details><summary>Reveal the worked answer</summary>

Training can change parameter values without changing their dimensions. Comparing logits from different weights confounds a numerical-kernel test.

</details>

## Mathematical connection

Read [Mathematics Unit 173](../11-maths-for-ai/173-evaluate-an-absolute-plus-relative-threshold.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](296-complete-an-inference-qualification-capstone.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
