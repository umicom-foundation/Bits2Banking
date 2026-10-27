# Lesson 281 — Separate prompt prefill from token decoding

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 161.

## Learning objective

First-token latency and subsequent-token latency measure different phases; neither is captured by an undifferentiated token-layer counter.

## Understand the mechanism

A decoder receives a prompt before it can emit a token. During **prefill**, it evaluates the incoming prompt and prepares any reusable key/value projections. The first token can be sampled from the last prompt-position logit row. During **decode**, the model accepts each newly sampled token and produces the next distribution. A KV cache changes the work of later steps, not the need to process a previously unseen prompt. In a streamed application the time to the first emitted token includes more than prefill: admission, queueing, transfers, sampler work and any retrieval may contribute. In a local synchronous test, those services are absent, so report exactly what the timer covers.

The existing Umicom prefix generator runs full-context calculations. The cached generator can reuse K/V while a prefix grows, but learned-absolute-position rollover forces a canonical rebuild. Measure each regime separately instead of reporting one average as the universal property of the model. This distinction is especially important when a four-token educational context rolls over far more often than a realistic model with a long context.

## Fully worked example

Assume 3 ms to create the session and evaluate the prompt, then 2 ms for each of four subsequent decode transitions. A five-token stream occupies about 11 ms of compute and orchestration: 3 + (4 × 2). The first-token wait is 3 ms in this simplified laboratory. Average end-to-end latency per token is 11 / 5 = 2.2 ms; it is neither the first-token delay nor the 2 ms transition time.

## Native C23 laboratory

Make a timeline that separates session creation, the first generated token, pending-token processing and every later sample. Annotate any position-rollover event. Do not label the total native benchmark runtime as TTFT when it measures an entire generation call.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 161](../11-maths-for-ai/161-calculate-time-to-first-token-vs-end-to-end.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** A request spends 10 ms queueing, 5 ms prefill, and 1 ms sampling its first token. What is the end-user TTFT?

<details><summary>Reveal the worked answer</summary>

16 ms, assuming other delays are zero. The 5 ms prefill alone is not TTFT.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](280-qualify-integrated-incremental-inference.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
