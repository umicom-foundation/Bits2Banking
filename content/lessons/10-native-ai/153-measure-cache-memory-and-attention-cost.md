# Lesson 153 — Calculate the memory cost of retaining attention keys and values

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Native C23 and AI engineering.

## Learning objectives

Understand the core engineering invariant, work through a bounded example, identify what Umicom Framework already implements and distinguish verified facts from proposed improvements.

## 1. The idea from first principles

Memory use can increase when inference avoids recomputing work. A KV cache retains two arrays—keys and values—for each transformer layer and retained token. With a full-width representation, a simple FP32 estimate is `2 × layers × tokens × channels × 4 bytes × concurrent sequences`.

For three layers, context length 16, width 32 and two simultaneous conversations, the payload estimate is `2 × 3 × 16 × 32 × 4 × 2 = 24,576 bytes`. This excludes metadata, fragmentation, attention scores, hidden states, queueing, allocator overhead and any temporary buffers. It is a **payload estimate**, not a sufficient process-memory budget.

Attention computation also depends on context length: each new query compares against all retained keys. A cache can avoid repeating old projections but still performs dot products for new queries. When extending context, always calculate both memory requirements and expected attention work.

## 2. Connect the lesson to Umicom Framework

The Framework already provides `UmiAiTrainingModelScalingEstimateBuild` for proposed model shapes. Use its `kvCacheFp32Bytes` as an estimate for the stated full-channel layout; its documentation explicitly excludes many runtime allocations. For live, small-scale measurements, use the existing tape's `UmiAiTrainingTapeMemoryInspect` and keep its tracked allocations distinct from process RSS.

Memory allocation and release remain Framework-owned. An application must not implement its own hidden matrix allocator to compensate for an underestimated budget.

## 3. Practice

**Question:** Using the same formula, how much FP32 KV payload would four layers, eight tokens, 16 channels and one sequence need?

<details><summary>Reveal the worked answer</summary>

`2 × 4 × 8 × 16 × 4 × 1 = 4,096 bytes`. This excludes buffers other than the two KV tensors.

</details>

## Further reading

Review [the multi-layer inference lesson](148-build-and-qualify-native-stacked-inference.md), [the introduction to the stacked decoder](121-build-a-real-multi-layer-transformer.md) and [the mathematics companion](../11-maths-for-ai/stacked-inference-mathematics.md).

*All numerical examples are educational; no model-generated source or financial transaction is executed. Service to Many Leads to Greatness.*
