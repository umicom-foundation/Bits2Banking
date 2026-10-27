# Lesson 282 — Measure complete inference calls with monotonic clocks

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Implementation:** C23 / Assembly where justified  
**Prerequisites:** Transformer Lessons 265–280 and Mathematics Unit 162.

## Learning objective

An elapsed wall-clock timer is not the same as process CPU time or a theoretical operation counter.

## Understand the mechanism

A defensible local measurement records a start instant immediately before the operation being compared and an end instant immediately after it. Operating systems may interrupt a process while the timer runs. That is not an error: the interruption forms part of observed wall-clock latency. The timing source should be monotonic so that wall-clock corrections do not create negative durations. On Windows a native program can use `QueryPerformanceCounter`; on POSIX systems it can use `clock_gettime(CLOCK_MONOTONIC)`.

Elapsed calls include allocation, checkpoint identity verification, prefill, token generation, cache rollover and destruction when all of those operations lie inside the timed boundary. Recording only the inner matrix multiplication cannot justify claims about complete prompt responses. Always state the boundary and whether model construction and weight loading are excluded. Native code can collect these timestamps without a PowerShell or Python runtime.

## Fully worked example

A timer produces start = 7,000,000,000 ns and end = 7,018,000,000 ns. Subtraction gives 18,000,000 ns, equal to 18 ms. A second trial returns 15 ms. Reporting only the 15 ms fastest run hides scheduling variation; preserve the full sample set and calculate a robust summary.

## Native C23 laboratory

Build the Framework-owned benchmark target with CMake, then inspect the `canonicalMedianNanoseconds` and `cachedMedianNanoseconds` values. Explain why both measurements include sampling and temporary tensor work rather than solely the attention kernel.

The numerical and inference services are owned by **Umicom Framework**. Existing samplers, stacked decoder, K/V store and training tape remain authoritative. Where this lesson discusses a proposed capability, it is labelled as a design rather than a verified implementation. No numerical equivalence or runtime acceleration is inferred merely from an operation count.

## Connect the mathematics

See [Mathematics Unit 162](../11-maths-for-ai/162-convert-monotonic-timestamps-to-milliseconds.md) for the corresponding numerical reasoning and a worked exercise.

## Self-assessment

**Question:** Why is `clock()` an unsuitable sole substitute for a monotonic elapsed timer?

<details><summary>Reveal the worked answer</summary>

It normally measures processor time consumed by the process, not all waiting and scheduling delays experienced by the caller.

</details>

## References and further reading

- [IETF LLM benchmarking terminology draft (work in progress)](https://datatracker.ietf.org/doc/draft-gaikwad-llm-benchmarking-terminology/)
- [vLLM documentation — inference serving concepts](https://docs.vllm.ai/en/latest/)

## Continue learning

[Previous lesson](281-separate-prompt-prefill-from-token-decoding.md) · [HTML study route](../../courses/llm-from-scratch/inference-benchmark-learning-path.html)

*Service to Many Leads to Greatness.*
