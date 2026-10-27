# Mathematics for AI — Unit 148: Separate TTFT, TPOT and throughput

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Calculate distinct inference-serving measurements.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

Suppose an inference service starts at time 0 ms, emits its first token at 120 ms, and emits three more tokens at 128, 138 and 146 ms. Time to first token is `TTFT=120 ms`. Under the inter-token-gap convention, subsequent gaps are `[8,10,8]` ms, so `TPOT=26/3≈8.67 ms`. The complete request duration is 146 ms for four tokens; dividing by four gives a different average that includes TTFT.

Across multiple requests, throughput is total generated tokens divided by a specified wall-clock interval. Report token definitions, whether prompt tokens count and the measurement boundary; otherwise comparisons are not reproducible.

## 3. Practice problem

**Question:** If ten requests together emit 500 tokens in 25 seconds of steady serving, what throughput does that observation represent?

<details>
<summary>Show the worked answer</summary>
<p><code>500/25=20</code> emitted tokens per second across the whole service, not 20 per request.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 263 — Measure prefill and decode performance separately](../10-native-ai/263-measure-prefill-and-decode-performance-separately.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](147-follow-greedy-speculative-token-verification.md) · [Browser learning path](../../courses/maths-for-ai/efficient-decoding-mathematics.html) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
