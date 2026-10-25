# Lesson 72 — Test Learned-Position Rollover and Checkpoint Compatibility

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework native KV-cache qualification  
**Illustrated companion:** [Lesson 72](../../courses/llm-from-scratch/lessons/72-test-learned-position-rollover.html)

## Learning objectives

Explain why evicting an old token changes learned absolute positions, calculate the resulting KV-cache work, distinguish numerical parity from runtime speed and recognise when a new positional-encoding scheme requires a new model-compatibility decision.

## 1. Eight positions cannot hold nine tokens

Our introductory Umicom decoder has a fixed attention context. Start with `A B C D E F G H` at absolute positions `0..7`. Append token `I`. The retained eight-token window becomes `B C D E F G H I`.

B used to occupy position 1; it now occupies position 0. Since the original decoder adds learned absolute-position information to a token representation, the key and value calculated for B at position 1 do not generally equal those required for B at position 0. That is not a pointer-management detail; **the mathematical input has changed**.

Consequently, the present `UmiAiTrainingKvCacheAppend` correctly rebuilds the new window on eviction rather than copying stale K/V rows.

## 2. Count the work before and after rollover

For a context length `C = 8`:

- Growing the first prefix from one token to eight computes **8 rows** in total.
- Appending token nine forces a complete rebuild of the retained eight positions, adding **8 more rows**.
- The cumulative count is **16 computed rows**, with **one window rebuild**.

| State | Retained tokens | Computed rows since cache creation | Full rebuilds |
|---|---|---:|---:|
| Before eviction | A through H | 8 | 0 |
| After first eviction | B through I | 16 | 1 |

For `C = 16`, the first eviction results in `16 + 16 = 32` cumulative rows. These are algorithmic work counts, not seconds or claims of faster text generation.

## 3. Compare against the original decoder again

The Framework's `UmiAiTrainingKvPositionQualify` verifies both the final full-prefix state and the state immediately after one eviction. It compares each cached logit with the canonical decoder evaluating the shifted context directly. A successful report requires all logits finite and their absolute differences within `0.00004`.

```c
#include "umicom/ai/training/kv_position_qualification.h"

UmiAiTrainingKvPositionQualification report = {0};
UmiStatus status = UmiAiTrainingKvPositionQualify(
    decoder, contextIds, 8U, nextTokenId, &report);

if (status == UMI_STATUS_OK) {
    /* Eight prefetched rows plus eight rebuilt rows after eviction. */
    uint64_t rows = report.computedRowsAfterRollover;
    uint64_t rebuilds = report.fullWindowRebuilds;
    (void)rows;
    (void)rebuilds;
}
```

The decoder, token IDs and report are caller-owned. The service performs no persistent writes or optimiser updates.

## 4. Changing positional encoding is a model change

Rotary position embeddings (RoPE), relative-position schemes and attention biases can provide different opportunities for KV reuse. But replacing learned absolute positions with another technique changes the decoder's forward calculation and often its parameterisation.

Do not reinterpret a previously trained checkpoint under a different positional scheme merely because both models use a function called “decode”. A responsible transition specifies: model architecture identity; checkpoint compatibility or retraining plan; canonical reference outputs; held-out quality evaluation; and independent tests before/after eviction.

The public C interface can remain stable without guaranteeing mathematically identical results between **different model architectures**. Keep these concepts separate.

## 5. A reliable acceptance record

A useful evidence record names the decoder checkpoint identity, source revision, context length, vocabulary size, token sequence, numerical tolerance, expected and observed work counters, compiler, host and test result. Verify checkpoint bytes remain unchanged across read-only qualification.

If an assertion fails after a test executable starts, diagnose the mathematical discrepancy. If the executable is missing or cannot load a dependency, fix the build or launch first; it does not demonstrate the decoder's arithmetic is wrong.

## Practise and check

**A.** If B moves from learned position 1 to 0, why must its cached representation be reconsidered?  
**Answer.** Its positional embedding is different, potentially changing later projections and attention values.

**B.** A context holds 16 tokens. What cumulative row count follows the first complete rollover?  
**Answer.** `32` rows, with one rebuild.

**C.** Can two model variants expose the same C ABI yet require separate checkpoints?  
**Answer.** Yes. Calling convention compatibility does not imply equal parameter meanings or outputs.

**Next:** [Lesson 73 — Unpadded prefix streaming](73-stream-growing-prefix-generation-in-c23.md).
