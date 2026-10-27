# Lesson 308 — Separate fixed-token replay from seeded sampling

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test separate fixed-token replay from seeded sampling within the bounded multi-layer Transformer.

## The underlying mechanism

A fixed-token replay isolates kernel arithmetic from probability-based token selection. It forces the reference and candidate to process exactly the same continuation IDs, which is necessary when examining every intermediate logit and projected cache row.

## Step-by-step worked example

A sampled-generation test instead runs two full inference sessions from the same prompt, nucleus settings and random seed, then compares emitted token IDs. A numerical mismatch might be hidden by identical sampled IDs, and small logit differences can occasionally change sampling branches.

## C23 implementation and Framework boundaries

Use `UmiAiTrainingStackedInferenceQualify` for fixed continuation IDs, then run the established canonical prefix sampler and incremental generator with identical options and seeds. Both tests are necessary but answer different questions.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

A successful fixed-token parity test cannot by itself prove that the sampling state machine consumes random numbers in the same order.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** Why does a kernel-release matrix need both fixed-token and seeded-generation tests?

<details><summary>Reveal the worked answer</summary>

One independently evaluates hidden numerical states; the other covers end-to-end sampling and session-state behaviour.

</details>

## Mathematical connection

Read [Mathematics Unit 184](../11-maths-for-ai/184-calculate-release-matrix-coverage.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](307-count-actual-executed-single-query-rows.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
