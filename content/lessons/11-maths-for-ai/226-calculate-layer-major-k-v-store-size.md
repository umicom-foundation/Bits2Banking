# Mathematics for AI — Unit 226: Calculate layer-major K/V store size

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

For unshared FP32 multi-head storage, each full session allocates keys and values for every layer, retained token position and channel. Use `S = 2 × L × T × C × sizeof(float)`. For general grouped-query geometry substitute `C = KVHeads × headChannels`; this is a capacity calculation, not proof that GQA is implemented in the decoder.

## Fully worked example

Given L=3 layers, T=8 tokens and C=16 channels with 4 bytes per scalar: S=2×3×8×16×4=3,072 bytes. Four physically retained stores require 12,288 bytes, excluding allocation overhead. The native checked planner protects every multiplication against size_t overflow.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** Compute FP32 raw K/V size for L=4,T=16,C=8.

<details><summary>Reveal full worked solution</summary>

2×4×16×8×4 = **4,096 bytes**.

</details>

## Discussion

Distinguish bytes from scalar counts, and raw K/V bytes from total process memory.

## Connect to native AI engineering

[LLM Lesson 367](../10-native-ai/367-acknowledge-only-committed-inference-work.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](225-reconcile-active-idle-and-physical-cache-bytes.md)

*Service to Many Leads to Greatness.*
