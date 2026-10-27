# Lesson 278 — Treat MQA and GQA as distinct model contracts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Avoid treating different K/V head topologies as transparent execution flags.

## 1. Concept and motivation

Multi-head attention stores separate K and V projections for each query head. Multi-query attention shares one K/V head among all query heads. Grouped-query attention uses fewer K/V heads than query heads. These layouts change weight parameterisation and checkpoint compatibility, not merely an attention-loop option. An existing checkpoint with eight independent K/V heads cannot be interpreted as a two-K/V-head model without an explicit conversion or uptraining method.

## 2. Worked example

With eight query heads and two K/V heads, groups have size four: query heads 0–3 read K/V head 0 and heads 4–7 read K/V head 1. Their K/V cache head count is one-quarter that of eight independent heads for identical head widths and number of tokens.

## 3. Native Framework implementation and evidence

Keep the present Umicom educational model on its established multi-head checkpoint shape. For a future GQA model, define separate weight shapes, head mapping, memory estimation and conversion qualification rather than modifying stored tensor dimensions in place.

## 4. Mathematical companion

Read [Mathematics Unit 156 — Calculate grouped-query cache ratios](../11-maths-for-ai/156-calculate-gqa-cache-head-ratio.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Does GQA automatically improve the measured latency of this particular C23 educational decoder?

<details>
<summary>Reveal the worked answer</summary>

No. A theoretical K/V memory reduction depends on model layout; measured benefit also depends on workload, kernel implementation and hardware.

</details>

## 6. Interpretation

Different attention topologies require explicit model metadata and validation.

## Continue learning

[277 — Measure CPU time and memory costs of a single query](277-measure-cpu-and-memory-costs-of-single-query.md) · [279 — Separate inference caching from RAG and fine-tuning](279-separate-kv-inference-from-rag-and-fine-tuning.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
