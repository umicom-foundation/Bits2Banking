# Mathematics for AI — Unit 146: Compare arithmetic intensity with bandwidth

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and previous attention units

**Learning objective:** Recognise when bytes moved dominate the execution limit.

## 1. Symbols and definitions

`T` denotes admitted causal tokens; `L` denotes Transformer layers; `Hq` is the query-head count; `Hkv` is the K/V head count; `d` is a head's channel width; `B` denotes bytes. The symbols are defined here to keep the exercise independent of a particular neural model size.

## 2. Step-by-step worked calculation

Arithmetic intensity is the number of arithmetic operations divided by bytes moved. Consider a simple dot-product loop performing two floating-point operations per scalar pair (one multiply and one add), reading two FP32 scalars (eight bytes). Its approximate intensity is `2/8=0.25 FLOP/byte`, ignoring cache reuse and output traffic.

If peak arithmetic throughput is 200 GFLOP/s and sustainable memory bandwidth is 50 GB/s, the simple roofline bound at intensity 0.25 is `min(200,50×0.25)=12.5 GFLOP/s`. This is a modelled upper bound, not a measured result; units must be consistent.

## 3. Practice problem

**Question:** At intensity `1 FLOP/byte` and bandwidth `40 GB/s`, what is the bandwidth roofline?

<details>
<summary>Show the worked answer</summary>
<p><code>40 GFLOP/s</code>, before the arithmetic throughput ceiling is applied.</p>
</details>

## 4. Connect the arithmetic to the native course

Read [LLM Lesson 255 — Measure key/value bandwidth per decode step](../10-native-ai/255-measure-key-value-bandwidth-per-decode-step.md) to see how these values become tensor shapes, buffer capacities or experimental measurements. Keep exact formulas separate from floating-point tolerances and measured execution times.

## Continue learning

[Previous unit](145-rotate-a-two-dimensional-position-pair.md) · [Next unit](147-follow-greedy-speculative-token-verification.md) · [HTML mathematics route](../../courses/maths-for-ai/efficient-decoding-mathematics.html)

*Service to Many Leads to Greatness.*
