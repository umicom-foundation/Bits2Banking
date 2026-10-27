# Lesson 237 — Budget single-query scratch memory

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Compare score-buffer and streaming-normaliser designs without assuming reduced memory is automatically faster.

## 1. Understand the problem

A straightforward kernel may allocate one score per retained key, compute a stable softmax and then accumulate values. That scratch requirement scales with `heads × validLength`. A streaming reduction can instead maintain a running maximum, denominator and weighted-value numerator per head; this can avoid storing all the scores, but it changes floating-point reduction order.

Both approaches must respect the Framework memory allocator, ownership conventions and cancellation boundaries. Per-thread scratch must not be shared unsafely; dynamically supplied shapes must be checked for multiplication overflow before allocating. A small scratch footprint is useful, but **latency depends on cache locality, vectorisation and allocation overhead**, not on element counts alone.

## 2. Fully worked example

With `heads=4`, `validLength=128`, `headWidth=16`, one FP32 score per head and token occupies `4×128×4 = 2,048` bytes. A per-head running FP32 output accumulator occupies `4×16×4 = 256` bytes, plus maxima, sums, temporary projections and alignment. Streaming can remove that score array; it does not remove K/V reads or the arithmetic required to calculate attention.

## 3. Engineering verification and connection to Umicom Framework

Record peak scratch bytes and allocation count separately from the K/V store capacity. Preallocate when the Framework lifetime rules permit it; on allocation failure, leave the inference session unchanged. Any streaming variant needs independent numerical tests against the canonical operator, especially for long prefixes and extreme logits.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 132](../11-maths-for-ai/132-calculate-cache-and-scratch-memory.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why is “2 KB fewer score bytes” not the same as “faster inference”?

<details>
<summary>Reveal the worked answer</summary>

It measures an intermediate allocation, not elapsed time. Different memory access order, exponentials, vector width and CPU cache behaviour may offset or exceed that saving.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](236-preserve-causal-masks-and-padding-semantics.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](238-compare-the-last-canonical-attention-row.md)

*Service to Many Leads to Greatness.*
