# Lesson 283 — Design paired canonical-versus-cached experiments

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 163.

## Learning objective

A performance comparison is invalid if the two paths use different models, prompts, sampling policies or seeds.

## Understand the mechanism

The reference and candidate paths must begin from the same checkpoint. Use identical prompt token IDs, tokenizer, context length, layer count, generation length, sampler configuration and initial random state. The canonical path must remain an independent calculation; comparing a candidate only with its own cached values cannot reveal a shared mathematical defect. Before timing, compare entire token-ID sequences and, where exposed by the model API, **all vocabulary logits** at each step. One successful sampled ID is a weak equality test because multiple nearby distributions may select the same token.

A paired experiment produces one reference measurement and one candidate measurement under a shared configuration. Pairing reduces variation from changes in machine load and model shape. It does not remove differences from thermal throttling, compilation flags or background activity. Store the run order, warmup count and raw measurements for further analysis.

## Fully worked example

For the same 8-token generation, suppose canonical and cached token lists are `[12,5,7,7,9,3,3,4]`. Exact ID parity passes; timing is allowed to proceed. If the cached sequence instead contains 10 at position 5, reject the comparison before producing any speed ratio. A faster wrong answer is not a valid optimiser.

## Native C23 laboratory

Use the C23 benchmark's input policy to run a greedy pair and a seeded top-p pair separately. If the sequence differs, investigate numerical invariants, not the tolerance by which timings are accepted.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 163](../11-maths-for-ai/163-calculate-paired-runtime-ratios.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Both paths generate identical IDs, but one logit differs by 0.01. Is that conclusive proof of numerical equivalence?

<details><summary>Reveal the worked answer</summary>

No. Exact IDs do not establish all-logit parity; a selected-token outcome can hide distribution differences.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](282-measure-complete-inference-calls-with-monotonic-clocks.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
