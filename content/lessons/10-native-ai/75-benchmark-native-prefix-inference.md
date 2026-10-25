# Lesson 75 — Benchmark Native Prefix Inference

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Language:** C23 · **Runtime owner:** Umicom Framework

## Learning objectives

Distinguish **numerical parity**, **computed token rows** and **measured elapsed time**. Learn why an unpadded growing-prefix generator must be compared with a reference using the *same positional policy*, rather than with the historical BOS-left-padded generator.

## 1. Decide what the experiment actually compares

The existing Umicom Framework decoder uses learned **absolute** positional embeddings. Its historical generation interface fills a short context with beginning-of-sequence (BOS) tokens on the left. The opt-in prefix session instead puts the first real token at position zero. These are different inputs to the same learned decoder. They may generate different tokens without either implementation being incorrect.

For a valid benchmark, the **canonical reference** must use the original decoder with real tokens at their prefix positions and future positions right-padded. A causal mask keeps those future padding positions from affecting an earlier logit. The comparison reads the last real token's logit row, not the last padding row. The cached path uses the same prompt, weights, position indices and sampling policy.

Use the Framework's existing `UmiAiTrainingPrefixBenchmarkRun`. Do not create another cache implementation in Bits2Banking.

## 2. Count work first

Let `C` be context length, `P` the length of the initial unpadded prompt and `G` the number of requested new tokens. Only `G − 1` generated tokens must be appended to obtain `G` samples because the last generated token remains pending.

The number of safe single-row appends is `S = min(G − 1, C − P)`. The remaining appends each require a full-window rebuild: `R = (G − 1) − S`.

- Canonical full-context row work: `C × G`.
- Cached row work: `P + S + C × R`.
- Rows avoided: the difference between those two counts.

For `C=8`, `P=3` and `G=12`: `S=5`, `R=6`. The reference computes `8×12=96` rows. The cache computes `3+5+(6×8)=56` rows. Therefore 40 rows, about 41.67% of the *row count*, are avoided.

This is **not** a measurement showing 41.67% less elapsed time. One path may use better vectorised kernels or incur less allocation overhead.

## 3. Call the existing native benchmark

```c
#include "umicom/ai/training/prefix_benchmark.h"

UmiAiTrainingPrefixBenchmarkPlan plan = {
    .generatedTokens = 12U,
    .warmupPairs = 1U,
    .measuredPairs = 5U,
    .seed = UINT64_C(7801)
};
UmiAiTrainingPrefixBenchmarkResult result = {0};

/* model, promptIds, promptLength and sampling belong to the caller. */
UmiStatus status = UmiAiTrainingPrefixBenchmarkRun(
    model, promptIds, promptLength, &sampling, &plan, &result);
```

The API includes validation and bounds. A successful report verifies identical generated tokens and the model's checkpoint identity before returning timing observations. The caller must not train or destroy the decoder concurrently.

## 4. Record measurements without overstating them

Measure repeated complete calls and alternate which path runs first. A warm-up may reduce first-use effects; its timing should not be mixed with measured trials. Record minimum, median and maximum wall time for each path, along with compiler settings, processor model, decoder configuration, seed, sampling policy and prompt.

A failed parity comparison invalidates the benchmark report. An unavailable or too-coarse clock, however, should be reported as **timing unavailable**, not as numerical failure or zero-cost inference.

## 5. Practical lab

From your existing Framework build, run the registered prefix benchmark tests rather than introducing a new benchmark implementation:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\learning\native-llm\prefix-work" `
      -B ".\build\windows-ucrt64-native-llm-prefix-debug" `
      -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-prefix-debug" --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-prefix-debug" `
      -R "^framework\.ai\.training\.prefix_benchmark_" `
      --output-on-failure --no-tests=error
```

**These are steps for the learner to run.** The lesson is not evidence that a particular computer has passed those tests.

## Exercises with answers

1. With `C=16`, `P=5` and `G=9`, how many appends? **Eight**. Since `C−P=11`, all eight are single-row; cached work is `5+8=13` rows versus `16×9=144` canonical rows.
2. Why not compare the cached prefix with a left-padded legacy generator? **It assigns different learned positions to the same real tokens**.
3. Which measurement is closer to user-visible latency: total token rows or wall-clock time? **Wall-clock time**, under a representative workload.

[Illustrated HTML lesson](../../courses/llm-from-scratch/lessons/75-benchmark-native-prefix-inference.html) · [Lesson 74: Prefix-generation parity](74-test-streaming-prefix-generation-parity.md)
