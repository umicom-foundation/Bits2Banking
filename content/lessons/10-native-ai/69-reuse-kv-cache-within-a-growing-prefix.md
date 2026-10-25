# Lesson 69 — Reuse the KV Cache Within a Growing Prefix

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework C23 prefix experiment  
**Illustrated course:** [Growing-prefix cache reuse](../../courses/llm-from-scratch/lessons/69-reuse-kv-cache-within-a-growing-prefix.html)

## Learning objectives

Explain when past keys and values can be safely reused, calculate the work of repeated prefixes, and state why this experiment does not replace the original text generator.

## Two different context policies

The preceding lessons used a **full, left-padded and eventually rolling** decoder context. The current model's learned absolute positional embeddings force a rebuild whenever retained tokens shift to different positions.

A **growing prefix** is a different workload. Start with the token at position zero. Inspect the next-token logits, then append one token at position one. Continue to position two, three and so on without evicting anything. Each old token keeps its original position, and causal attention prevents past tokens from observing future ones.

This is a valid opportunity to retain keys and values as long as the decoder's position and attention semantics remain unchanged.

## Count repeated work

Suppose we inspect logits after prefixes of length one through six. Independent recomputation uses:

`1 + 2 + 3 + 4 + 5 + 6 = 21 rows`.

Incremental recomputation adds one row at a time:

`1 + 1 + 1 + 1 + 1 + 1 = 6 rows`.

The cache therefore avoids `21 − 6 = 15` rows. As a fraction of the reference, `15 / 21 ≈ 71.4%`.

For any valid prefix length `N`:

\[
\text{reference rows} = \frac{N(N+1)}{2},\quad
\text{incremental rows} = N,\quad
\text{avoided rows} = \frac{N(N-1)}{2}.
\]

This measures rows, not elapsed time or floating-point operations. Longer prefixes can make each new attention row more expensive, even when the number of new token rows is one.

## The Framework contract

```c
#include "umicom/ai/training/kv_prefix_reuse.h"

UmiAiTrainingKvPrefixWorkEstimate estimate = {0};
UmiStatus status = UmiAiTrainingKvPrefixWorkEstimateBuild(
    &decoderConfig, 6U, &estimate);
/* The expected result is 21 reference, 6 incremental, 15 avoided rows. */
```

The Framework reuses the canonical `UmiAiTrainingKvCachePrefill`, `UmiAiTrainingKvCacheAppend` and cache allocation planner. It does not create an alternative Transformer or change saved checkpoints.

## Why not change existing generation automatically?

The legacy generator's BOS padding, position shifts, sampling and checkpoint behaviour are part of its qualified semantics. Replacing them with a growing-prefix policy would change the model input, even if both approaches happened to output the same token on one example. This experiment proves a narrower claim: identical inputs and fixed positions allow mathematically valid incremental reuse **before eviction**.

## Exercises and worked answers

**Question A.** Calculate row counts for nine inspected prefixes.  
**Answer.** `9×10/2 = 45` independent rows and `9` incremental rows; `36` avoided, or `80%`.

**Question B.** Why can an old key at position two be retained after a new token arrives at position five?  
**Answer.** Its original position and causal input context are unchanged.

**Question C.** What happens when adding a ninth token to an eight-token context?  
**Answer.** The full context needs an eviction or other explicit policy; the current absolute-position cache rebuilds shifted representations.

**Key point:** Reuse depends on invariant token positions, not simply on a cache existing in the program.

**Next:** [Test prefix reuse against decoder logits](70-test-prefix-reuse-with-real-decoder.md).
