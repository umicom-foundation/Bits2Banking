# Mathematics for AI — Unit 147: Follow greedy speculative token verification

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Identify which proposed tokens are safe to commit.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

A draft proposes `[A,B,C,D]`. The target's greedy next-token checks along the accepted prefix are `[A,B,X,...]`. Only `A,B` match. At the third position, the target returns `X`, so the draft's `C` and its following `D` are not valid continuations of the target's greedy trajectory.

This elementary check is not the distribution-preserving speculative sampling algorithm. For random sampling, acceptance and correction must follow a mathematically specified scheme using both target and draft probabilities.

## 3. Practice problem

**Question:** If the target first disagrees with the draft at position 1 (zero based), how many draft tokens can be accepted?

<details>
<summary>Show the worked answer</summary>
<p>Only the first token, at position 0.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 260 — Explain speculative decoding and verification](../10-native-ai/260-explain-speculative-decoding-and-verification.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](146-compare-arithmetic-intensity-with-bandwidth.md) · [Next unit](148-separate-ttft-tpot-and-throughput.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
