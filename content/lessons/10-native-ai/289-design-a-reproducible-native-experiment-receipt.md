# Lesson 289 — Design a reproducible native experiment receipt

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 169.

## Learning objective

A benchmark result is evidence only when its configuration and identity can be reconstructed.

## Understand the mechanism

A reproducible result records the model checkpoint hash, tokenizer/vocabulary identity, prompt tokens, sampling policy, seed, number of warmups and measured pairs, build profile, compiler, operating system, CPU and timing boundaries. It also preserves raw observations and numerical pass/fail gates. The value of this receipt is traceability, not a promise that elapsed nanoseconds will repeat exactly. Two hosts can produce identical generated tokens but different timings.

Keep the structure machine-readable for later comparison. The native C23 benchmark service returns measurements and counters without writing into a repository or modifying the model. A product- or test-owned receipt writer may store the report once an explicit output path and approved lifecycle are defined. Distinguish an immutable content identity from source trust: a digest detects modification, but by itself it does not establish who created the file or whether its contents are appropriate.

## Fully worked example

A receipt with `model_sha256`, `prompt_ids=[65,66]`, `generated=8`, `warmups=1`, `pairs=5`, `seed=31` and `clock=monotonic` is more informative than a screenshot reading `45 tokens/s`. Yet hardware, compiler options and actual raw timing samples are still required for a scientifically interpretable comparison.

## Native C23 laboratory

Draft a text schema for one complete result; separate reference and candidate sections and include a parity flag. Leave secret tokens, personally identifiable source material and internal machine credentials out of examples.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 169](../11-maths-for-ai/169-calculate-release-gate-coverage.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Does SHA-256 alone prove that the benchmark or checkpoint was produced by a trusted party?

<details><summary>Reveal the worked answer</summary>

No. A hash provides an integrity identifier; authentication and provenance require separate evidence.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](288-benchmark-growing-prefix-and-window-rollover-separately.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
