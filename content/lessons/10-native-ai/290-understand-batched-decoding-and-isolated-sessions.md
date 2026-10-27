# Lesson 290 — Understand batched decoding and isolated sessions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 170.

## Learning objective

Throughput for many requests is not the same performance metric as latency for one request.

## Understand the mechanism

A batched inference engine may share a model's weight buffers across sessions but each request has its own token history, sampler state and K/V ownership. Continuous batching admits and completes requests at different times; this can improve aggregate device utilisation, especially on accelerators. It can also increase queueing or time-to-first-token for a short request behind long work.

The present Umicom educational stacked session is synchronous, bounded and caller-serialised. It is not a continuous-batching scheduler. Before adding one, define per-request ownership, fairness, bounded queues, cancellation and model identity. Request isolation is a correctness property, not only a performance feature: mixing K/V rows from different prompts creates cross-session information leakage. A scheduler must never treat one request's position count as another's.

## Fully worked example

A device serves four requests in 200 ms and emits 80 tokens across them. Aggregate throughput is 80 / 0.2 = 400 tokens/s. A single user could still wait 150 ms for their first token; aggregate throughput does not describe that experience.

## Native C23 laboratory

Sketch a scheduler queue with two long prompts and three short prompts. Mark each request's separate K/V store and immutable checkpoint identity. Identify where cancellation takes effect before a batch executes.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 170](../11-maths-for-ai/170-separate-system-throughput-from-user-latency.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Can two requests share the same model weights while retaining independent K/V caches?

<details><summary>Reveal the worked answer</summary>

Yes, if their mutable states, positions and random streams are isolated and protected by the runtime contract.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](289-design-a-reproducible-native-experiment-receipt.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
