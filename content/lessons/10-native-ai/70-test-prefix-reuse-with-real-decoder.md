# Lesson 70 — Test Growing-Prefix Reuse Against Decoder Logits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework C23 cache-comparison service  
**Illustrated course:** [Prefix reuse and decoder testing](../../courses/llm-from-scratch/lessons/70-test-prefix-reuse-with-real-decoder.html)

## Learning objectives

Check every vocabulary logit rather than only the predicted token, verify work counters, understand numerical tolerances and keep measured CPU-time observations separate from guarantees.

## Define the two computations

The independent-prefix reference calls cache **prefill** afresh for each prefix length: 1, 2, 3, …, N. The incremental path calls **prefill** for the first token, then **append** for each following token. Both operate on the same unchanged decoder weights, same token IDs and same absolute positions.

For six prefixes, the expected token-row totals are 21 versus 6. That arithmetic alone is not sufficient. Every computed output must also agree.

## Compare all logits

A logit is a score assigned to one token in the vocabulary. If we compare only the largest score's index, large numerical mistakes in other scores could remain hidden. Instead, the Framework `UmiAiTrainingKvPrefixPerformanceCompare` compares each vocabulary logit and checks that differences stay within its stated absolute tolerance of `0.00004`.

```c
#include "umicom/ai/training/kv_prefix_reuse.h"

UmiAiTrainingKvPrefixPerformance result = {0};
UmiStatus status = UmiAiTrainingKvPrefixPerformanceCompare(
    model, tokenIds, 6U, &result);

if (status == UMI_STATUS_OK) {
    /* Prefix outputs and observed work counters satisfied the contract. */
    size_t compared = result.matchingPrefixes;
    uint64_t reference = result.observedReferenceRows;
    uint64_t incremental = result.observedIncrementalRows;
    (void)compared;
    (void)reference;
    (void)incremental;
}
```

This test uses **two invocations of the qualified KV-cache kernel**. Their agreement qualifies scheduling and reuse, but it is not wholly independent arithmetic validation. A separate comparison with canonical decoder logits remains necessary before making stronger claims.

## Verify the actual workload

A complete report checks that:

- Six prefixes were compared.
- Independent recomputation counted 21 rows.
- Incremental reuse counted six rows.
- No rolling-window rebuild occurred.
- Every compared logit stayed within the declared tolerance.

If any check fails, the comparison must not publish a misleading successful result. A failure-atomic result structure prevents a caller from mistaking partially populated numbers for accepted evidence.

## Run registered tests

The Framework provides a focused independent prefix laboratory. After its successful build, use:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
ctest --test-dir '.\build\windows-ucrt64-native-llm-prefix-debug' `
    -R '^framework\.ai\.training\.kv_prefix_' `
    --output-on-failure --no-tests=error
```

If a test is `Not Run`, first verify that the corresponding executable exists. A missing executable is a build/invocation problem, not a numerical verdict.

## Exercises and worked answers

**Question A.** Why compare every logit rather than just the top token?  
**Answer.** A wrong distribution can still give the same argmax; sampling and loss depend on other scores too.

**Question B.** Could fewer computed rows produce slower CPU time in one run?  
**Answer.** Yes, because of allocation, memory access, overhead, compiler behaviour or scheduling.

**Question C.** Does this experiment prove full-window generation can use old keys after eviction?  
**Answer.** No. Shifting learned positions invalidates the retained keys and values; the present experiment stops before eviction.

**Key point:** A performance claim needs a precisely identified workload, independent numerical checks, reproducible measurements and explicit limits.

**Further study:** [Designing adapter-based fine-tuning](low-rank-adaptation-and-fine-tuning.md).
