# Lesson 287 — Distinguish KV allocation from peak process memory

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 167.

## Learning objective

The cache owner accounts for some allocations, not the entire memory consumed by training or inference.

## Understand the mechanism

The K/V cache stores projections across layers and token positions. Its theoretical byte count follows `2 × layers × tokens × KV-heads × head-dimension × bytes-per-element`. A concrete cache owner may reserve a full context upfront, so retained-token count and allocated capacity are different quantities. Other memory consumers include model parameters, temporary attention scores, tensor tape nodes, allocator overhead, stacks, loaded libraries and operating-system page mappings.

Never call the sum of K/V floats "peak RAM". The Framework's reserved K/V byte counter is a bounded component accounting measurement. Peak resident set size (RSS) requires an operating-system observation of the whole process. A rigorous report presents both rather than mixing them. For more advanced models, sliding windows, grouped-query attention and quantisation change the cache shape; measure the exact representation, not an assumed FP32 dense MHA layout.

## Fully worked example

Two layers, eight KV channels, six context positions and FP32 values require 2 × 2 × 8 × 6 × 4 = 768 bytes of K/V payload. The process may occupy many megabytes even though this particular cache reports 768 bytes.

## Native C23 laboratory

Inspect the cached session report's `reservedKvBytes`, then compare it with an independent process-memory measurement. Label the first as cache payload and the second as process resident memory.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 167](../11-maths-for-ai/167-estimate-actual-kv-payload-bytes.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** A cache reports 768 bytes and the process RSS is 20 MiB. Are these contradictory?

<details><summary>Reveal the worked answer</summary>

No. The values measure different ownership boundaries; the process includes more than K/V payload.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](286-qualify-full-logit-and-generated-token-parity.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
