# Lesson 275 — Set finite-precision acceptance thresholds

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · Native C23

**Learning objective:** Choose error metrics before interpreting candidate/reference differences.

## 1. Concept and motivation

Numerical comparison should start with exact tensor shape, finite FP32 values and immutable model identity. For each element, report absolute error `|candidate-reference|`; a scale-aware check can accept `|difference| <= atol + rtol*|reference|`. A maximum over all vocabulary positions helps detect rare outliers. Record the worst offending index and both operands rather than hiding it behind an average.

## 2. Worked example

Suppose reference logits are `[0.01, 10, -20]` and candidate logits are `[0.010004, 10.00001, -20.00004]`. With `atol=1e-5` and `rtol=1e-6`, the first discrepancy of `4e-6` passes, the second error of `1e-5` passes by the combined bound and the third error of `4e-5` fails because its combined bound is only `3e-5`. Use actual binary values in tests and state strict or inclusive comparison.

## 3. Native Framework implementation and evidence

For the one-query operator, first test a direct attention-row parity fixture, then measure actual complete decoder logits with the existing `IncrementalNear` predicate. Distinguish numerical tolerances for attention outputs, full logits and sampling decisions.

## 4. Mathematical companion

Read [Mathematics Unit 154 — Compute absolute-plus-relative error](../11-maths-for-ai/154-compute-absolute-plus-relative-error.md). Check each numerical assumption against the example above before running a program.

## 5. Exercise

**Question:** Can a test be fixed simply by increasing its tolerance until it passes?

<details>
<summary>Reveal the worked answer</summary>

No. A widened threshold changes the claim. The investigator must establish the expected floating-point error bound and document why it is justified.

</details>

## 6. Interpretation

Logit-level tolerances must not conceal NaN, infinity, shape mismatch or invalid model state.

## Continue learning

[274 — Verify greedy and sampled sequence parity](274-verify-greedy-and-sampled-sequence-parity.md) · [276 — Build a multi-axis integration-test matrix](276-build-a-multi-axis-integration-test-matrix.md) · [Browser learning path](../../courses/llm-from-scratch/integrated-attention-learning-path.html)
