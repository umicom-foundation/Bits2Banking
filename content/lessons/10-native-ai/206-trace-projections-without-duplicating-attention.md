# Lesson 206 — Trace projections without duplicating attention mathematics

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Follow a read-only callback through the established Transformer block and explain ownership.

## Why this matters

The existing `UmiAiTrainingTransformerBlockForwardWithProjections` was introduced so Framework components could alter a selected projection without duplicating the attention, layer-normalisation and feed-forward code. A passive trace can reuse exactly that extension point. In the observer, the callback performs the ordinary tape matrix multiplication for **all six** projection roles. Only when the role is Key or Value does it also copy a completed tensor into a separate capture buffer.

This is an important separation of concerns: the Transformer still owns the computation, the training tape still owns tensor lifetimes, and the K/V store owns durable copies of rows. The trace must not mutate the canonical weights, train a model, execute generated source or retain a pointer into the tape. Even the error path calls the existing rollback operation.

The uninstrumented forward remains the default. Its C23 entry point and call order are unchanged. A trace is an explicitly requested diagnostic, with additional copying overhead; it is not an optimisation.

## Work through the numbers and tensor shapes

In one Transformer layer, the trace observes K and V, but **Q remains a transient value** used by attention. That distinction prevents the cache owner from mistaking Q for a persistent key. The wire/storage layout is `[layer][time][channel]`, not `[head][layer][time]`. Heads are contiguous slices within the channel dimension; the Framework's established attention operator still interprets those slices.

Example: with two layers, four tokens and four channels, the key at layer one, token two, channel three has flat index `(1 × 4 + 2) × 4 + 3 = 27`. Indexing a different layer, token or channel is a correctness error even if every value is finite.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** Which parts of the model are calculated again when a projection trace is requested?

<details><summary>Reveal the worked explanation</summary>

The entire original forward pass is executed: embeddings, normalisation, K/Q/V, masked attention, both residuals, feed-forward and logits. Only copies of K/V are retained. The original model is not replaced by a parallel implementation.

</details>

## Continue studying

[Previous lesson](205-observe-keys-and-values-in-the-real-transformer.md) · [Next lesson](207-compare-projection-trace-and-canonical-logits.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/206-trace-projections-without-duplicating-attention.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
