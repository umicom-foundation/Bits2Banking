# Lesson 304 — Rebuild all layers on absolute-position rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** Native C23; Assembly only where justified.

## Learning objective

Understand, calculate and independently test rebuild all layers on absolute-position rollover within the bounded multi-layer Transformer.

## The underlying mechanism

A learned absolute-position decoder assigns position-dependent embeddings. Once the context is full, discarding the oldest token shifts surviving tokens to new positions and changes their inputs. Their K/V rows must be recomputed at every affected layer.

## Step-by-step worked example

For context four, history `[A,B,C,D]` followed by token `E` becomes `[B,C,D,E]`. The token `B` moves from position one to zero. Reusing `B`’s old K/V row would feed attention a projection computed with the wrong positional embedding.

## C23 implementation and Framework boundaries

The qualified path uses the canonical full-context projection trace and `UmiAiTrainingStackedKvStoreReplaceRolled` with all layers and all context rows. The service counts these as full rebuilds, not single-query incremental steps.

The reference implementation is the existing Umicom Framework stacked decoder and its training tape. Its public APIs own numerical operations and memory lifetimes. Reusable diagnostics belong in Framework; educational manuscripts and demonstrations belong in Bits2Banking. This lesson is not a substitute for running integrated qualification against the actual source checkout.

## How to diagnose a failed run

Rotary-position models may allow different cache policies, but no such property transfers automatically to this particular learned-absolute-position model family.

A useful failed-test record includes the checkpoint identity, token sequence, context length, layer count, expected and observed scalar values, numerical tolerance and the exact position at which divergence begins. This permits the error to be reproduced without changing the training data or using a different decoder.

## Exercise

**Question:** With prompt length two, context six and nine continuation tokens, how many transitions use full-window replacement?

<details><summary>Reveal the worked answer</summary>

Four transitions fill the remaining positions; the next five transitions roll the context, so five full replacements are required.

</details>

## Mathematical connection

Read [Mathematics Unit 180](../11-maths-for-ai/180-calculate-full-window-replacement-counts.md) to reproduce the relevant arithmetic by hand.

## Continue learning

[Previous lesson](303-read-back-retained-cache-state-after-each-append.md) · [Browser learning path](../../courses/llm-from-scratch/numerical-qualification-learning-path.html)
