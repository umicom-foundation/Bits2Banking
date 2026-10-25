# Lesson 80 — Qualify position-bound generation and benchmark evidence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

Run generation with an approved model/context pairing, identify when KV-cache work measurements are available and explain why a comparison is valid only when both paths implement the same mathematical task.

## 1. One decoder, distinct prompt semantics

The canonical learned-absolute decoder supports two explicit inference conventions. Historical **BOS-left-padded** generation locates a short prompt at the end of a full context. **Growing-unpadded** generation starts at position zero and expands while room remains. Because positions affect model activations, equal prompts and seeds do not guarantee equal output between conventions.

`UmiAiTrainingPositionBoundGenerate` verifies a supplied `UmiAiTrainingPositionContract` before and after calling the appropriate *existing* generator. Tokens, count and evidence become visible only after the complete request succeeds.

```c
#include "umicom/ai/training/position_admission.h"

/* model and approvedContract refer to an already reviewed checkpoint. */
const size_t promptIds[] = {109U, 114U, 120U};
const UmiAiTrainingNucleusOptions policy = {1.0F, 1U, 1.0F};
size_t generatedIds[6] = {0};
size_t generatedCount = 0U;
UmiAiTrainingPositionGenerationEvidence evidence = {0};

UmiStatus status = UmiAiTrainingPositionBoundGenerate(
    model, &approvedContract,
    UMI_AI_POSITION_CONTEXT_GROWING_UNPADDED,
    promptIds, 3U, &policy, 6U, UINT64_C(80),
    generatedIds, 6U, &generatedCount, &evidence);
```

The token IDs represent raw generation output. They are not automatically valid source code, safe SQL or a financial instruction. Nothing in this function should execute them.

## 2. Reproduce the work estimate

For context capacity **C = 8**, initial prompt length **P = 3** and requested generation length **G = 12**, the full-context reference calculates `C × G = 96` token rows.

The growing cache leaves its final generated token pending. Therefore it performs `G − 1 = 11` appends: the first `C − P = 5` appends add one row each, while the remaining six require whole-window rebuilds. Total cached rows are:

`P + 5 × 1 + 6 × C = 3 + 5 + 48 = 56`.

That is **40 fewer computed token rows** (approximately 41.7% of 96). It is not a measured 41.7% decrease in execution time. CPU caches, memory traffic, vectorised matrix operations and process scheduling all influence elapsed time.

## 3. Report measurements that exist

`UmiAiTrainingPositionGenerationEvidence.cacheWorkAvailable` distinguishes measured cache statistics from absent measurements. The historical canonical generator does not expose the same cache-work counters; its unavailable readings must not be presented as zeros *measured* in a test.

The established `UmiAiTrainingPositionBoundBenchmark` only admits the growing-unpadded policy because its independent reference follows that policy. It delegates numerical parity, measurements and model-checkpoint integrity to Framework-owned services; Bits2Banking does not implement a separate benchmark engine.

## 4. Exercise

Take **C = 10**, **P = 4**, **G = 8**. The reference costs 80 rows. There are seven appends: six single-row additions and one ten-row rebuild. The candidate costs `4 + 6 + 10 = 20` rows, saving 60 rows (75%). Explain why even this larger work saving is not automatically a 75% latency improvement.

**Takeaway:** only evidence from equivalent computations can justify an optimisation claim.

[Illustrated lesson](../../courses/llm-from-scratch/lessons/80-qualify-policy-bound-generation-and-benchmarks.html) · [Previous](79-admit-model-checkpoints-before-inference.md) · [Next](81-introduce-rotary-position-mathematics.md)
