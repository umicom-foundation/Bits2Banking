# Lesson 291 — Reason about prefix sharing and cache ownership

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 171.

## Learning objective

Prefix reuse requires identical tokens, model weights, positional policy and cache shape, plus explicit lifetime management.

## Understand the mechanism

Two prompts beginning with the same token IDs may share early causal K/V projections when the model and its positional semantics are identical. A reusable prefix needs a stable cache key including checkpoint identity, tokenizer version, exact prefix tokens, attention configuration and position policy. Text that merely looks equivalent is insufficient: a byte-tokeniser can encode different strings into different token sequences.

A shared cache also requires ownership rules. Immutable pages can be reference-counted, but a writer must not extend a shared page in place when another request still observes it. Cancellation must release only that request's references. A model update invalidates cached projections derived from previous weights, even if the prompt happens to be unchanged. Prefix sharing is not implemented by the bounded educational session in this batch; the lesson defines prerequisites for an independent future implementation.

## Fully worked example

Prompts A = [1, 5, 9, 4] and B = [1, 5, 9, 7] have three identical initial token IDs. With fixed absolute positions and unchanged weights, K/V rows for positions 0–2 can be candidates for sharing. If the model is retrained, the shared prefix length remains three but the old cached tensors are no longer valid.

## Native C23 laboratory

Draw an ownership graph in which two requests reference an immutable prefix block. Cancel one request, confirm the other can still read, and then plan what happens when the model checkpoint changes.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 171](../11-maths-for-ai/171-model-shared-prefix-reference-counts.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Why does matching display text not prove cache-prefix equivalence?

<details><summary>Reveal the worked answer</summary>

The tokenizer, exact token IDs and positional/model contracts may differ even when the visible text appears similar.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](290-understand-batched-decoding-and-isolated-sessions.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
