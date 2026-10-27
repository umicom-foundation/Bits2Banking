# Lesson 288 — Benchmark growing-prefix and window rollover separately

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 168.

## Learning objective

The learned absolute position policy forces full recomputation after eviction, so cache benefits depend on prompt and generation lengths.

## Understand the mechanism

Incremental reuse is valid while earlier tokens keep their absolute position indices. A prompt of length two in a six-token context can append four new positions without changing previous indices. Once the window is full, evicting the oldest token shifts every remaining token to a new learned position. This changes its embedding and propagates through all Transformer layers. Reusing old K/V rows after that shift would be mathematically unsound.

Measure growth-phase steps and rollover-phase steps independently. A short-context educational benchmark may spend most of its generation in full rebuilds, making cached inference slower overall despite one-query attention being cheaper during growth. Report the first rollover and at least one repeated rollover; otherwise the test does not cover its dominant correctness boundary.

## Fully worked example

Context = 6, initial prompt = 2, generated outputs = 8. The first generated ID comes from prefill, so there are seven pending-token transitions. Four transitions extend the prefix from 2 → 6. The remaining three transitions rebuild a rolled six-token window. In a model with two layers, each rebuild evaluates 6 × 2 token-layer rows.

## Native C23 laboratory

Compare separate runs with prompt lengths 1, 3 and full-context 6. Keep layer count and seed fixed. Observe how work counters and elapsed time change as the rollout share increases.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 168](../11-maths-for-ai/168-count-rollover-transitions-with-pending-samples.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** With a full six-token prompt and four generated outputs, how many subsequent transitions require rollover?

<details><summary>Reveal the worked answer</summary>

Three. The first output is sampled from prefill; before each of the next three outputs a pending token forces a full-window rebuild.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](287-distinguish-kv-allocation-from-peak-process-memory.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
