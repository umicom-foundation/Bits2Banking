# Lesson 279 — Separate inference caching from RAG and fine-tuning

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Keep runtime execution optimisations conceptually separate from changing knowledge or weights.

## 1. Concept and motivation

A KV cache stores numerical projections associated with the current token history and fixed model parameters. Retrieval-augmented generation selects external documents to place into the prompt; it changes input context, not necessarily the model weights. Fine-tuning changes model parameters and invalidates caches derived from the previous checkpoint. These mechanisms can coexist, but their validity rules remain distinct.

## 2. Worked example

A local assistant retrieves three passages and inserts 120 tokens into a prompt. Those tokens must be prefetched through the model before generation. If retrieval changes the prompt between requests, a KV cache from the previous request is not automatically reusable; it must have exactly compatible prefix tokens, positions and model identity.

## 3. Native Framework implementation and evidence

Model execution remains Framework-owned. The retrieval layer supplies explicit reviewed prompt text and source citations; the decoder neither secretly searches files nor silently updates weights. An application uses the Framework AI contracts instead of embedding separate attention mathematics.

## 4. Mathematical companion

Read [Mathematics Unit 158 — Bound reused prefix validity](../11-maths-for-ai/158-bound-reused-prefix-validity.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Will changing a retrieved document alter cached K/V rows even if the model weights are identical?

<details>
<summary>Reveal the worked answer</summary>

If the new prompt token sequence or positional interpretation differs, yes. The cache is tied to its prefix and positional semantics, not just a checkpoint digest.

</details>

## 6. Interpretation

A faster decoder is not inherently a more accurate model or better retrieval system.

## Continue learning

[278 — Treat MQA and GQA as distinct model contracts](278-keep-multi-query-and-grouped-query-as-new-contracts.md) · [280 — Qualify the integrated incremental decoder](280-qualify-integrated-incremental-inference.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
