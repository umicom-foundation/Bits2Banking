# Lesson 76 — Qualify Benchmark Evidence and Protect Checkpoints

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Implementation:** existing Umicom Framework C23 services

## Learning objectives

Interpret a performance report without mistaking numerical correctness for performance, detect invalid experiments, distinguish CPU time from wall-clock time, and ensure inference never changes the training checkpoint.

## 1. A benchmark is a claim backed by evidence

A single successful run is not enough to conclude that one inference method is faster. CPU frequency scaling, instruction-cache effects, system load, compiler optimisation, memory allocation and scheduling can all affect a short timing result. A reliable benchmark first establishes that both paths perform equivalent **model mathematics**.

The Framework's `UmiAiTrainingPrefixBenchmarkResult` distinguishes a valid comparison from a mere observation. It stores paired-run counts, comparison identities, work counters, checkpoint integrity and availability indicators for the timing clocks.

## 2. Qualification gates

| Gate | Required evidence |
|---|---|
| Model identity | Exact same native decoder and unchanged checkpoint bytes |
| Context semantics | Same unpadded growing-prefix policy on both paths |
| Sampling | Same seed, temperature, top-K and top-p |
| Numerical behaviour | Every generated token matches; relevant canonical logits qualified separately |
| Work accounting | Observed KV row and rebuild counters match the estimator |
| Repeatability | Independent trial pairs generate identical sequences |
| Timing quality | Report whether clocks are available, sufficiently resolved and monotonic |

If the paths produce different token IDs, **do not publish a successful speed comparison**. It would compare different computations. Conversely, a clock returning an unusable duration is not evidence that the model's mathematics failed.

## 3. Understand clocks

**Wall-clock time** is elapsed real time; it includes waiting for resources. **Process CPU time** counts CPU consumption charged to the process; it may include unrelated threads. A fast path can have high CPU usage, and two paths can have the same counted token rows but different elapsed times.

The native benchmark uses platform timing sources and reports what was actually available. Results should be replicated on a representative machine under comparable conditions. Avoid comparing a Debug executable directly with a Release executable and attributing all differences to KV caching.

## 4. Read a successful report

```c
#include "umicom/ai/training/prefix_benchmark.h"

/* Evidence is a successfully returned Framework benchmark result. */
if (evidence.checkpointUnchanged != 1) {
    /* Do not present this as qualified immutable-model evidence. */
}
if (evidence.wallClockAvailable != 0) {
    /* Compare canonical and incremental medianWallSeconds. */
}
```

A `tokenFingerprint` field supports quick comparison of generated token sequences but is not a cryptographic signature. Model checkpoint checks and trusted publisher decisions are separate operations.

## 5. Worked interpretation

Suppose verified counting shows 96 canonical rows and 56 cached rows. That supports a statement about **40 fewer rows** under this workload. Suppose also that median wall-clock readings are 4.2 ms and 4.7 ms for canonical and cache paths. The cache appears slower in those observations despite calculating fewer rows.

No contradiction exists. Row-count reduction is not a general speedup theorem. A production performance claim would require more repeated representative tests, error bars, stable environments and device-specific benchmarking.

## 6. Why failures must preserve outputs

The reporting API stages its result. Invalid plans, mismatched tokens or changed checkpoint bytes must not leave a half-updated result that another component could interpret as successful evidence.

A useful negative test fills the output structure with a sentinel, makes a call with zero measured pairs, and compares every output byte afterward. The correct behaviour is a rejected status and **no report mutation**.

## Practice and answers

1. A comparison has correct token parity but no measurable clock interval. Can it still report correctness? **Yes**; it must label timing unavailable.
2. A benchmark detects one changed token in a 64-token output. Can it publish a speedup? **No**, because the computations did not produce equivalent results.
3. Does a SHA-256 digest prove who published a checkpoint? **No**; authenticity requires an independent trust and signature policy.

[Illustrated HTML lesson](../../courses/llm-from-scratch/lessons/76-qualify-benchmark-evidence.html) · [Lesson 75: Benchmark a prefix](75-benchmark-native-prefix-inference.md)
