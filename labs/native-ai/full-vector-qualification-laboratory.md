# Native C23 laboratory — Canonical versus incremental Transformer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Objective

Verify the actual bounded stacked decoder rather than an invented or downloaded model. Compare every active vocabulary-logit row of the canonical forward and the projection trace, every incremental new-token logit, each new K/V projection and every retained cached K/V scalar. Count full-window rebuilds separately from safe growing-prefix appends.

## Prerequisites

A configured C23 compiler, CMake, Ninja and the Umicom Framework source tree are required. The Framework training tape, tokenizer, stacked checkpoint, KV store and single-query attention must be available. These commands illustrate a developer-facing native laboratory; executable correctness must be established by the real build and test output.

## Build the opt-in native laboratory

On Windows, from the directory containing the `framework` subdirectory:

```powershell
cmake -S .\framework\learning\native-ai-stacked-qualification -B .\build\native-ai-stacked-qualification -G Ninja -DBUILD_TESTING=ON
cmake --build .\build\native-ai-stacked-qualification --parallel 2
ctest --test-dir .\build\native-ai-stacked-qualification --output-on-failure --no-tests=error
```

The tests are normal C23 executables launched by CTest. They do not require Python or PowerShell for the mathematical implementation. A C23 parity-only laboratory is separately available under `framework/learning/native-ai-inference-parity`.

## Reproduce the scalar counts

For context six, two layers, channel width eight, vocabulary 260, prefix two and eight fixed continuation IDs, predict the growing-prefix transitions (`6-2=4`) and full replacements (`8-4=4`). Expected incremental logits compared: `4×260=1,040`. Expected proposed K/V comparisons: `4×2×8×2=128`. Calculate retained K/V readback independently from the sequence of active rows.

## Qualification questions

1. Why must every absolute-position rollover rebuild all retained layers?
2. Why does a passing fixed-token trace not prove deterministic top-p sampling?
3. Why does no error in generated token IDs fail to establish complete logit equivalence?
4. Why is a Release paired benchmark necessary before claiming measured acceleration?

**Expected interpretation:** Numerical equivalence, state lifetime, cache ownership and runtime measurement are independent acceptance dimensions. A failure in any required dimension prevents the corresponding release claim.
