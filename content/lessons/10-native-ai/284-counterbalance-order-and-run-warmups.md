# Lesson 284 — Counterbalance execution order and run warmups

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 164.

## Learning objective

Running every canonical trial first may bias timings through cache warming, CPU frequency and memory pressure.

## Understand the mechanism

Run an untimed warmup for each path. Then alternate execution order across measured pairs: reference → cached, followed by cached → reference. This is **counterbalancing**. It reduces one systematic source of bias, although it cannot control operating-system scheduling, temperature or other processes. Record compilation mode and device information alongside results.

The educational Framework service uses bounded warmups and measured pairs, deliberately alternating order. A short laboratory with five pairs illustrates the procedure but does not support an inference about every computer or prompt. Longer studies should use multiple independent processes, workload order randomisation where appropriate and variation measurements. Keep reproducibility (fixed model and seed) separate from temporal determinism: a repeatable output sequence can still have variable elapsed time.

## Fully worked example

Three pairs produce canonical times [9.2, 9.0, 9.1] ms and candidate [8.9, 9.4, 8.8] ms. The middle observations are similar even though one candidate run is the fastest. Selection of the single best time would exaggerate the result.

## Native C23 laboratory

Write a two-column observation sheet labelled A/B order and B/A order, with run number, clock source, checkpoint ID, and complete generation duration. Verify that each pair produced exactly the same token IDs.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 164](../11-maths-for-ai/164-compare-alternating-ab-run-orders.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Why does an untimed warmup not count towards the measured sample size?

<details><summary>Reveal the worked answer</summary>

Because the experiment explicitly reserves warmups for stabilising code/data paths and reports only the later trials as measurements.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](283-design-paired-canonical-versus-cached-experiments.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
