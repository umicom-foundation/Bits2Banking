# Lesson 67 — Measure Decoder and KV-Cache Work Correctly

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework C23 inference modules  
**Illustrated course:** [Native decoder and cache work](../../courses/llm-from-scratch/lessons/67-measure-decoder-and-kv-cache-work.html)

## Learning objectives

Calculate how many token rows a full-context decoder computes, explain why moving learned absolute positions invalidates cached keys and values, and distinguish arithmetic work from memory use and elapsed time.

## The eight-position example

The current teaching decoder accepts a fixed context length. Let that length be `C = 8` tokens. A full-context next-token prediction computes eight token rows. To generate twelve tokens, the reference path performs:

`referenceRows = C × generatedTokens = 8 × 12 = 96`.

This is a useful **work count**. It is not a count of CPU instructions or a measured number of milliseconds.

When the prompt is shorter than eight tokens, the canonical generator supplies left-hand beginning-of-sequence padding to fill the context. After generating more tokens, the oldest token is eventually evicted from the full rolling window. The remaining tokens shift to earlier absolute positions. Because the current decoder adds **learned absolute-position embeddings**, those retained token representations are now different from the ones used to calculate their old keys and values.

Correctness requires a rebuild. Cache entries that represent the old positions cannot simply be relabelled.

## Calculate the qualified cached path

The existing Framework session builds a full eight-row cache first. Eleven subsequent token advances in this twelve-token request require full-window rebuilds:

```text
Initial prefill                 = 8 rows
Rolling-window rebuilds        = 11
Rows per rebuild               = 8
Total computed rows            = 8 + 11 × 8 = 96
```

Both paths compute 96 rows. This **does not** mean their clock times must be equal: allocations, copies, branch behaviour, and cache locality can differ.

## Framework work estimate

The public `umicom/ai/training/generation_performance.h` header exposes `UmiAiTrainingGenerationWorkEstimateBuild`. With a valid eight-token `UmiAiTrainingDecoderConfig`, the request below produces a model-aware estimate:

```c
#include "umicom/ai/training/generation_performance.h"

UmiAiTrainingGenerationWorkEstimate work = {0};
UmiStatus status = UmiAiTrainingGenerationWorkEstimateBuild(
    &decoderConfig, 3U, 12U, &work);
/* On success, both work counters are 96 for this positional policy. */
```

The Framework cache allocation planner supplies `cacheHeapBytes`. That excludes the decoder training tape, temporary stack storage, allocator overhead and the operating system's resident-set accounting. Never turn one counter into an unsupported total-memory claim.

## Exercises and worked answers

**Question A.** A model uses a context of 16 and generates seven tokens. How many reference rows does it compute?  
**Answer.** `16 × 7 = 112` rows. The current full-context cache also computes `16 + 6×16 = 112` rows.

**Question B.** Why does an old key from position 7 become invalid when its source token is shifted to position 6?  
**Answer.** It was computed from a different learned positional representation, so it no longer corresponds to the same model input.

**Question C.** Could a streaming interface still be useful if it saves no token rows?  
**Answer.** Yes. It lets an application retrieve tokens incrementally, display progress, and cancel with clear ownership and lifetime controls.

**Key point:** First preserve numerical and positional correctness; then measure computational work and real performance separately.

**Next:** [Compare inference performance with verified evidence](68-qualify-native-generation-performance.md).
