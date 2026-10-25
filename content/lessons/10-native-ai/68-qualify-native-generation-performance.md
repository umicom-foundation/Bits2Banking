# Lesson 68 — Benchmark Native Generation Using Reproducible Evidence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework C23 performance comparison  
**Illustrated course:** [Generation performance and evidence](../../courses/llm-from-scratch/lessons/68-qualify-native-generation-performance.html)

## Learning objectives

Compare two generation paths fairly; prove token-for-token agreement before reporting work counters; distinguish process CPU time, wall-clock latency and perceived streaming responsiveness.

## What must remain identical?

A defensible comparison uses the same decoder and immutable weights, prompt token IDs, initial random seed, temperature, top-K limit, top-p threshold and requested output length. If any of these differ, changed tokens could reflect changed sampling rather than a defect in the cache.

The existing Framework function `UmiAiTrainingGenerationPerformanceCompare` executes the reference nucleus generator and the persistent KV-cache session under matched settings. It refuses to publish a success report if the token sequences differ or the measured cache rows conflict with its estimator.

## Read the C23 report

```c
#include "umicom/ai/training/generation_performance.h"

UmiAiTrainingGenerationPerformance report = {0};
UmiStatus status = UmiAiTrainingGenerationPerformanceCompare(
    model, promptTokenIds, promptLength, &samplingPolicy,
    12U, UINT64_C(7801), &report);

if (status == UMI_STATUS_OK) {
    /* The Framework has verified identical token IDs and row accounting. */
    size_t matching = report.matchingTokens;
    uint64_t cachedRows = report.observedCachedRows;
    (void)matching;
    (void)cachedRows;
}
```

The example presumes the caller already owns `model`, `promptTokenIds`, `promptLength` and `samplingPolicy`. It does not create a second decoder, train a model, or execute generated text.

## Work counters are not clock measurements

Three commonly confused measurements are:

- **Computed token rows:** the algorithmic quantity counted by the cache and estimator.
- **Process CPU time:** aggregate processor time spent inside the process, which may differ from elapsed wall-clock time.
- **Wall-clock latency:** time a user waits, including scheduling, I/O and any other delays.

The current report optionally uses `clock()` for process CPU time. Very short calls may be too small for the clock resolution; a reported zero is not proof of instantaneous inference. A real performance study repeats representative requests, includes warm-up, records compiler and CPU details, and reports variability rather than one attractive number.

The current learned-absolute-position generator still rebuilds a full window when positions shift. Reducing allocations or improving memory locality may change runtime, but it is not evidence of fewer token rows.

## Run existing Framework acceptance tests

From your Framework workspace on Windows, configure and build the established native LLM laboratory. Then execute the qualified performance checks:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
ctest --test-dir '.\build\windows-ucrt64-native-llm-debug' `
    -R '^framework\.ai\.training\.generation_performance' `
    --output-on-failure --no-tests=error
```

Build the registered test executables before invoking CTest. `Not Run` means the executable did not start; it is neither a passing mathematical test nor a proven numerical defect.

## Exercises and worked answers

**Question A.** Why is comparing generated strings weaker than comparing token IDs?  
**Answer.** A byte decoder can produce NUL or non-UTF-8 bytes; display conversions can hide token differences.

**Question B.** If two paths compute the same number of rows but one is faster, what might explain it?  
**Answer.** Data locality, temporary allocations, cache residency, compiler optimisations and scheduling.

**Question C.** What do equal CPU times prove?  
**Answer.** Only observations for those runs. They do not establish general performance parity on other data, hardware or configurations.

**Key point:** An optimisation report should specify what was compared, what was verified, what was measured and what remains unknown.

**Next:** [Reuse the cache while a token prefix grows](69-reuse-kv-cache-within-a-growing-prefix.md).
