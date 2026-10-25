# Lesson 73 — Stream a Growing Prefix with Native C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework `prefix_generation` services  
**Illustrated companion:** [Lesson 73](../../courses/llm-from-scratch/lessons/73-stream-growing-prefix-generation-in-c23.html)

## Learning objectives

Distinguish BOS-left-padding from an unpadded initial prefix, create an explicit streaming inference session, calculate token-row work before and after a context rollover and identify where application presentation ends and Framework-owned neural processing begins.

## 1. Why the position policy must be explicit

The original Umicom native generator left-pads a short prompt to a **full** context with beginning-of-sequence (BOS) tokens. In an eight-position context, the three tokens `i n t` appear at positions 5, 6 and 7. The next-token prediction uses the last row.

The separate `UmiAiTrainingPrefixGenerationSession` starts the same three tokens at positions 0, 1 and 2, without left padding. The initial prediction uses row 2. This leaves five free positions before the first eviction.

These are two different positional policies. Because the decoder has learned absolute embeddings, the generated sequences need not match. The new policy is opt-in and does not replace the historical API or change trained weights.

## 2. Create a session using Framework services

```c
#include "umicom/ai/training/prefix_generation.h"
#include <stdint.h>

const size_t sourcePrefix[] = {109U, 114U, 120U}; /* Byte IDs for int. */
const UmiAiTrainingNucleusOptions policy = {1.0F, 1U, 1.0F};
UmiAiTrainingPrefixGenerationSession *session = NULL;
UmiStatus status = UmiAiTrainingPrefixGenerationSessionCreate(
    model, sourcePrefix, 3U, &policy, UINT64_C(7801), &session);

if (status == UMI_STATUS_OK) {
    for (size_t i = 0U; i < 6U; ++i) {
        size_t tokenId = 0U;
        status = UmiAiTrainingPrefixGenerationSessionNext(
            session, &tokenId);
        if (status != UMI_STATUS_OK) break;
        /* Send token ID to a presentation buffer; never execute generated text. */
    }
    UmiAiTrainingPrefixGenerationSessionDestroy(session);
}
```

`model` is an existing caller-owned decoder. The session copies the prompt, sampling policy and RNG state, owns its KV cache, and borrows the model. It must be destroyed before model training or destruction. Cancelling a session means destroying its retained state; this small laboratory does not automatically stop on an EOS token.

## 3. Calculate exact workload

Define:

- `C`: maximum model context length.
- `P`: number of initial prompt tokens (nonzero, at most `C`).
- `G`: number of new tokens requested (1–256 in this laboratory).
- `A = G − 1`: cache appends, because the last generated token is still pending.
- `S = min(A, C − P)`: appends that need one new row.
- `R = A − S`: appends requiring full rebuild after eviction.

The resulting work is:

`canonicalRows = C × G`  
`cachedRows = P + S + C × R`  
`rowsAvoided = canonicalRows − cachedRows`.

For `C = 8`, `P = 3`, `G = 12`:

`A = 11`, `S = 5`, `R = 6`, `canonicalRows = 96`, `cachedRows = 3 + 5 + 6×8 = 56`, so **40 rows are avoided**, around **41.7% of the reference's row count**.

For a prompt already filling the context, `P = C`, `S = 0`; all subsequent appends rebuild the window. A cache cannot promise a speedup solely from its name.

## 4. Check the Framework's estimate

```c
#include "umicom/ai/training/prefix_generation.h"

UmiAiTrainingPrefixGenerationWorkEstimate estimate = {0};
UmiStatus status = UmiAiTrainingPrefixGenerationWorkEstimateBuild(
    &decoderConfig, 3U, 12U, &estimate);

if (status == UMI_STATUS_OK) {
    uint64_t expectedRows = estimate.cachedComputedRows;
    uint64_t expectedRebuilds = estimate.cachedWindowRebuilds;
    (void)expectedRows;
    (void)expectedRebuilds;
}
```

This calculation is part of the Framework. No Bits2Banking application code should implement a second estimator. The `cacheHeapBytes` field concerns the cache allocation only; it does not include the decoder's full training tape, OS allocations or peak process memory.

## 5. Streaming is about ownership and responsiveness

A GUI can request one token, display it, request another or cancel. The GUI should not implement KV cache semantics, neural weights, numerical sampling or checkpoint encoding. Model output is **untrusted content**, not an instruction to execute code or alter a financial transaction.

## Practise and check

**A.** For `C = 8`, `P = 3`, `G = 6`, calculate cached rows.  
**Answer.** `A = 5`, `S = 5`, `R = 0`, `cachedRows = 3 + 5 = 8`; canonical work is `8 × 6 = 48` rows.

**B.** For `C = 8`, `P = 8`, `G = 6`, calculate cached rows.  
**Answer.** `A = 5`, `S = 0`, `R = 5`, `cachedRows = 8 + 5×8 = 48`, equal to the canonical row count.

**C.** Does generating fewer rows prove fewer seconds?  
**Answer.** No; benchmark actual elapsed time and CPU use with the same weights, policy, workload and build configuration.

**Next:** [Lesson 74 — Verify prefix-generation parity](74-test-streaming-prefix-generation-parity.md).
