# Lesson 292 — Budget multi-head versus grouped-query KV memory

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 172.

## Learning objective

Grouped-query attention reduces the number of K/V heads without removing query heads.

## Understand the mechanism

In ordinary multi-head attention the model commonly has one independent K and V projection per query head. Grouped-query attention (GQA) allows several query heads to share one K/V head, reducing retained projections and memory bandwidth. It changes the model's parameter shapes and attention mapping. It is not an optimisation that can be enabled by simply dropping rows from a checkpoint trained for standard MHA.

The native educational stacked decoder uses its original attention-head and projection layout. That checkpoint family remains unchanged. Future GQA support needs a separate architecture identifier, explicit head-to-KV mapping, shape-aware persistence and independent numerical qualification. This lesson treats the memory equations as a planning tool rather than claiming current production support.

## Fully worked example

With 16 query heads, 4 KV heads, head width 64, 24 layers, 4,096 tokens and two FP16 bytes per value, GQA K/V payload is 2 × 24 × 4,096 × 4 × 64 × 2 = 100,663,296 bytes ≈ 96 MiB per sequence. Standard MHA with 16 KV heads would be about 384 MiB, four times larger.

## Native C23 laboratory

Calculate the payload for 8,192 tokens and 8 KV heads under the same layer count and precision. Explain why the result is a storage estimate and not total VRAM usage.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 172](../11-maths-for-ai/172-compare-mha-and-gqa-cache-capacity.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Under the worked configuration, how many K/V heads are represented by each query-head group?

<details><summary>Reveal the worked answer</summary>

16 query heads / 4 KV heads = four query heads per shared K/V head.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](291-reason-about-prefix-sharing-and-cache-ownership.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
