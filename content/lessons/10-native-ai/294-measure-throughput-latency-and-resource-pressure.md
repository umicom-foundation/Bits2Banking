# Lesson 294 — Measure throughput, latency and resource pressure separately

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 170.

## Learning objective

A system can improve token throughput yet worsen interactive response time or peak memory.

## Understand the mechanism

Server benchmarks should report throughput (tokens or requests per second), time to first token, inter-token latency, memory usage, and saturation behaviour as separate dimensions. Workload distribution matters. A stream of short prompts with long completions stresses different parts of the runtime than long documents asking for one answer. Measure the prompt and completion length distributions, concurrency, admission and cancellation.

A single-request native benchmark is a foundation for CPU regression detection; it does not measure queueing, fairness, multi-user security or the throughput of a distributed serving platform. Draft terminology for TTFT and TPOT exists in IETF work, while public inference benchmarking papers analyse specific workload profiles. Cite what was measured, on which hardware, under what load. For realistic enterprise evaluation, use consented or appropriately licensed corpora and independent held-out prompts.

## Fully worked example

At concurrency 1, 30 tokens produced in 0.6 s gives 50 tokens/s. At concurrency 4, the system emits 120 tokens in 1.2 s, giving 100 aggregate tokens/s. Throughput doubled while response completion may take longer for an individual request. Both figures can be true.

## Native C23 laboratory

Design three workload profiles: short-interactive, long-document and mixed-concurrency. List TTFT, P50/P95 inter-token latency, errors, memory and generated-token counts; do not invent missing measurements.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 170](../11-maths-for-ai/170-separate-system-throughput-from-user-latency.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Can an engine report double the tokens per second while users see slower individual responses?

<details><summary>Reveal the worked answer</summary>

Yes. Aggregate throughput and per-request latency have different denominators and can move in opposite directions.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](293-treat-kv-quantisation-as-a-new-numerical-contract.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
