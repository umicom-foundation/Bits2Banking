# Lesson 88 — Verify Rotary Training Results Without Overstating Them

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework, C23

## Learning outcomes

Understand the difference between a smaller measured loss and a verified model improvement; interpret gradient magnitudes; verify failure-atomic results; and distinguish process memory, tape-owned memory and model quality.

This manuscript accompanies the [illustrated HTML lesson](../../courses/llm-from-scratch/lessons/88-verify-rope-optimisation-and-results.html). [Mathematics Unit 12](../11-maths-for-ai/12-finite-differences-and-floating-point.md) explains numerical tolerances from first principles.

## 1. A training report is evidence about a specific experiment

Suppose `initialLoss = 0.025` and `finalLoss = 0.020`. Their difference is:

`lossChange = finalLoss − initialLoss = 0.020 − 0.025 = −0.005`

The negative value establishes that the **declared experiment's** objective fell by 0.005. It does not establish better completions, unbiased answers, financial safety, or reliable generalisation.

Measure loss from a fresh forward pass **after** each update; a stale pre-update graph would misrepresent the final weights.

## 2. Read the first gradient norm

A 4 × 4 projection matrix has 16 gradient components. The L2 norm is:

`||g||₂ = √(g₁² + g₂² + … + g₁₆²)`

For a small vector `[3, 4]`, the norm is `√(3² + 4²) = √25 = 5`. The norm tells us the aggregate gradient magnitude. It does not tell us that the update will improve loss or that numerical gradients are correct.

Independent finite differences can provide additional evidence. For a scalar weight `w`, compare `(L(w + ε) − L(w − ε)) / (2ε)` against the analytic gradient using a tolerance declared *before* viewing results.

## 3. Verify separate engineering contracts

| Test | Supported conclusion | What it cannot prove |
| --- | --- | --- |
| Declared loss decreases | One training objective improved | Broad language quality |
| Query/key norms are finite | These measured gradients are numerically finite | Every derivative is correct |
| Rejected operation retains result bytes | Output publication is failure-atomic in the tested case | Every operating-system fault is handled |
| Identical inputs produce equivalent outputs | Local reproducibility | Bitwise equality across all CPUs |
| Tape high-water mark recorded | Accounted tape-owned peak allocation | Total process RAM or GPU usage |

Do not report a successful model if a test executable was `Not Run`; execution, numerical assertions and benchmarks are separate gates.

## 4. Run focused Framework regressions

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\framework\learning\native-llm\prefix-work" -B ".\build\windows-ucrt64-native-llm-prefix-debug" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ".\build\windows-ucrt64-native-llm-prefix-debug" --target umicom-ai-training-rotary-optimisation-convergence-test umicom-ai-training-rotary-optimisation-rejections-test --parallel 2
ctest --test-dir ".\build\windows-ucrt64-native-llm-prefix-debug" -R "^framework\.ai\.training\.rotary_optimisation_" --output-on-failure --no-tests=error
```

These commands must run against the actual Framework checkout; this lesson does not claim they have passed on your machine.

## 5. Worked exercise and answers

**Problem:** An experiment reports `initialLoss = 0.03` and `finalLoss = 0.02`. Calculate the change, then state one valid and one invalid conclusion.

**Answer:** `0.02 − 0.03 = −0.01`. Valid: measured teaching MSE fell by 0.01. Invalid: a production LLM now generates trustworthy source code. Language quality requires independent held-out evaluation, not this isolated numeric optimisation exercise.

**Review:** Why verify a result after the last update? Why record compiler/toolchain identity? Why use independently computed numerical gradients? Why is a SHA-256 content digest different from a trusted publisher's signature?

**Next:** [Read the independent gradient acceptance lesson](../../courses/llm-from-scratch/lessons/89-audit-rotary-gradients-against-an-oracle.html).
