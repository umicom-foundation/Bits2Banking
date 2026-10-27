# Lesson 263 — Measure prefill and decode performance separately

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Produce reproducible latency evidence without confusing different phases.

## 1. Understand the concept

Model inference is a sequence of distinct workloads: prompt tokenisation, cache allocation, prefill, the first sample, repeated decode steps, context rollover and output byte handling. **Time to first token (TTFT)** includes work that a single-query decoder kernel may not change. **Time per output token (TPOT)** should be defined precisely; publications differ on whether they average only inter-token gaps after the first token or divide the full request time.

For a fair test, compare identical model checkpoint, prompt IDs, hardware, process affinity, compiler optimisation, sampling seed and output token counts. Warm up each code path, record multiple paired runs and alternate execution order to reduce thermal and scheduling bias.

## 2. Work through the numbers

Suppose one request spends 20 ms tokenising and pre-filling, then emits four tokens with inter-token gaps of `[6,5,7]` ms after the first token. TTFT must be measured at the actual first emission boundary. Under the inter-token-gap definition, TPOT is `(6+5+7)/3=6 ms`, not `20/4=5 ms`. Dividing the entire request by four produces a different metric and must not carry the same label.

For five paired full-session runs, compare paired differences rather than only two unrelated means. Include median and a spread statistic, and note when the sample is too small to support a strong speed conclusion.

## 3. Apply the concept to native model engineering

Performance counters from an arithmetic kernel count theoretical operations executed by that kernel, not the whole Transformer. The native educational kernel allocates scratch buffers and does not yet replace the original incremental attention composition. Reporting a whole-model speedup at this stage would be unsupported.

Use a Release build for latency, separate sanitizer builds for memory correctness, and check full-vector numerical parity before treating the outputs as interchangeable.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 148](../11-maths-for-ai/148-separate-ttft-tpot-and-throughput.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** A request emits five tokens and has four measured post-first gaps of 3, 5, 4 and 8 ms. What is its TPOT under the inter-token-gap convention?

<details>
<summary>Reveal the worked answer</summary>
<p><code>(3+5+4+8)/4=5 ms</code> per subsequent token. TTFT is measured separately.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[262 — Preserve checkpoint and cache portability](262-preserve-checkpoint-and-cache-portability.md) · [264 — Complete the native inference qualification capstone](264-complete-the-native-inference-qualification-capstone.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
