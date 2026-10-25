# Lesson 74 — Verify Streaming Prefix Generation and Observed Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** Existing Umicom Framework native prefix-generation tests  
**Illustrated companion:** [Lesson 74](../../courses/llm-from-scratch/lessons/74-test-streaming-prefix-generation-parity.html)

## Learning objectives

Build an independent reference for unpadded prefix generation, compare token IDs across streaming and one-shot execution, verify actual KV-cache workload counters, and keep the original BOS-left-padded generator's semantics intact.

## 1. Keep the reference's positions the same

A short, unpadded prefix places real tokens at positions `0..P−1`. The canonical decoder requires a full input context. To compare against it, place the real prefix on the **left**, append BOS tokens on the **right**, and read the logit row for the last **real** token:

```text
Prefix:           A B C
Canonical input:  A B C BOS BOS BOS BOS BOS
Reference row:        ^  (index 2)
```

This is valid for causal attention: position 2 does not attend to the future positions 3–7. Reading the final BOS row would test the wrong question. Padding the left would also test a different positional policy, because the real tokens would occupy positions 5–7.

## 2. Qualify three related paths

The Framework tests compare the native unpadded session against:

1. The original `UmiAiTrainingDecoderLogits` computation using right padding and the existing seeded nucleus sampler.
2. The one-shot `UmiAiTrainingDecoderGeneratePrefixNucleus` wrapper around the session.
3. The session itself when tokens are pulled one by one across both prefix growth and the first context rollover.

All paths use the same immutable decoder, prompt IDs, seed and sampling policy. The test must compare **every emitted token ID**, not just rendered text. Byte-token output may contain `NUL` or bytes that do not form a printable UTF-8 string.

The original historical full-BOS-left-padded generator is intentionally **not** a parity reference for this opt-in mode. It is still a valid public API with different positional semantics.

## 3. Do not accept plausible-looking counters

For context `C`, prompt length `P` and output count `G`, compute the expected work as in Lesson 73. Then ask the cache service what it actually did. The one-shot wrapper should withhold a successful output if observed work differs from the accepted model of the operation.

| Observation | Expected for `C=8`, `P=3`, `G=12` |
|---|---:|
| Generated tokens | 12 |
| Cache rows computed | 56 |
| Full-context window rebuilds | 6 |
| Retained tokens before the last sample is appended | 8 |

The final generated token remains pending, so the cache's retained-token count is evaluated before that final append. Distinguish the number of **tokens returned** from the number **already incorporated into the cache**.

## 4. Regression integrity

The real native regression covers short prompts, full prompts, greedy policies, seeded top-p sampling, repeated rollovers, malformed requests, insufficient output buffers and unchanged checkpoint bytes. If a single token diverges, the result is not numerical parity even if work counters match.

The test must also prove that a failed one-shot request does not publish partially generated output, while a streaming session may already have published earlier successful tokens. An internal error after cache advancement makes that session terminal: destroy it rather than retrying a partially advanced state.

## 5. Build and run against your actual Framework checkout

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
$env:Path = 'C:\msys64\ucrt64\bin;' + $env:Path

cmake -S '.\framework\learning\native-llm\prefix-work' `
    -B '.\build\windows-ucrt64-native-llm-prefix-debug' `
    -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build '.\build\windows-ucrt64-native-llm-prefix-debug' `
    --target umicom-ai-training-prefix-generation-parity-test `
             umicom-ai-training-prefix-generation-rejections-test `
    --parallel 2

ctest --test-dir '.\build\windows-ucrt64-native-llm-prefix-debug' `
    -R '^framework\.ai\.training\.prefix_generation_' `
    --output-on-failure --no-tests=error
```

Only report passing results after these compiled tests have actually executed on the relevant checkout. A fixture or test double is not independent production-decoder evidence.

## Practise and check

**A.** A prefix has `P = 3` in a context `C = 8`. Which canonical logit row is the reference?  
**Answer.** Row index `P − 1 = 2`, not row 7.

**B.** Why must the original generator's left-BOS-padding semantics remain unchanged?  
**Answer.** Moving real tokens changes learned absolute embeddings and potentially every prediction; the new mode is an explicitly different inference policy.

**C.** What does a source-code assistant do with an emitted token?  
**Answer.** Present it as untrusted output; it does not execute it or treat it as authorisation for a code change.

**Further study:** [Adapter checkpoints and model identity](adapter-checkpoints-and-model-identity.md) · [Finite-difference evidence](../11-maths-for-ai/12-finite-differences-and-floating-point.md).
