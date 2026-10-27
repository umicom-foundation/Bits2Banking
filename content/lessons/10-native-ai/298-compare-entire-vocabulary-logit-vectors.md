# Lesson 298 — Compare entire vocabulary-logit vectors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test compare entire vocabulary-logit vectors within the bounded multi-layer Transformer.

## The underlying mechanism

Selecting the same next token is weaker than reproducing the original model distribution. Two logit vectors can have the same argmax while assigning very different relative probabilities, affecting top-p sets and later sampled outputs. A release gate therefore compares all vocabulary positions.

## Step-by-step worked example

Let canonical logits be `[2.0, 1.0, -1.0]` and candidate logits be `[2.0, 1.9, -1.0]`. Both select token zero greedily, but the second candidate assigns much more weight to token one. With a 260-token byte vocabulary, the release gate inspects 260 values for every qualifying position.

## C23 implementation and Framework boundaries

Call the canonical decoder and the projection-trace decoder on identical right-padded fixed contexts. Compare active rows, then compare the incremental proposal against the canonical final row. Record the count of scalar comparisons rather than only “passed”.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A full-context buffer includes padding positions. Those positions are useful for computation but are not part of the active-prefix acceptance population; do not misreport them as validated input-token rows.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Two decoders produce the same greedy token. Does that establish numerical equivalence?

<details><summary>Reveal the worked answer</summary>

No. Compare every vocabulary logit (within a declared tolerance) and the K/V projections where those are reused.

</details>

## Mathematical connection

Read [Mathematics Unit 174](../11-maths-for-ai/174-count-active-prefix-vocabulary-logits.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](297-freeze-the-checkpoint-before-inference-qualification.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
