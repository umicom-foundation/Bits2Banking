# Lesson 286 — Qualify full-logit and generated-token parity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 166.

## Learning objective

Correctness comparisons should distinguish exact token parity, bounded numerical logit parity and model-identity integrity.

## Understand the mechanism

A cache can preserve the same sampled token while subtly changing the model's predicted probabilities. Compare every vocabulary logit against the independent canonical decoder, not merely the argmax. A practical floating-point acceptance rule uses an absolute component and a relative component: `abs(a-b) <= atol + rtol * max(abs(a),abs(b))`. Choose tolerances before seeing results. Different compute orders may produce small round-off differences, but non-finite results always fail.

For stacked models, verify the new key/value row at every layer, test 1-, 2- and 3-layer cases, compare short and full prompts, and traverse the first and repeated rollover boundaries. Make the checkpoint identity part of the cache contract: a training step invalidates projections retained from older weights. Only after these tests should timing results enter an engineering comparison.

## Fully worked example

Atol = 0.0001 and rtol = 0.00001. For reference 2.00000 and candidate 2.00008, the threshold is 0.0001 + 0.00001 × 2.00008 = 0.0001200008. Error 0.00008 passes. An error of 0.0003 fails.

## Native C23 laboratory

Extend the independent parity matrix beyond the bundled paired token-ID benchmark by comparing every logit and K/V row using the existing Framework qualification services. Keep these stronger checks separately identified from the elapsed benchmark.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 166](../11-maths-for-ai/166-apply-absolute-plus-relative-logit-tolerances.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Is a successful four-token sequence sufficient to prove the decoder numerical path correct?

<details><summary>Reveal the worked answer</summary>

No. It may conceal changed logits or K/V rows; full-vector and multi-layer parity testing remains necessary.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](285-report-medians-spread-and-performance-uncertainty.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
