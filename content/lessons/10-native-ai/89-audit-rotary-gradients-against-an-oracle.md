# Lesson 89 — Audit Rotary Gradients Against an Independent Numerical Oracle

**Bits to Banking · Native AI · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation authority:** Umicom Framework (C23)

## What you will learn

A training run may appear successful because its loss decreases, yet its
calculated gradients can still be wrong. This lesson explains how to verify
rotary attention with a **mathematically independent reference calculation**.
The corresponding [illustrated lesson](../../courses/llm-from-scratch/lessons/89-audit-rotary-gradients-against-an-oracle.html)
provides the original examples and teaching diagrams.

You should be able to distinguish a training result from a qualification test,
calculate a central finite difference and explain why repeating the same
implementation is not an independent check.

## A small problem that can be inspected

Our Framework laboratory considers three token rows, four channels and two
attention heads. The query and key matrices each contain **16 weights**. The
real Umicom training tape applies matrix multiplication, rotary positions,
causal attention, a defined mean-squared-error objective and reverse-mode
backpropagation. The independent test calculates the same tiny mathematical
problem without calling the tape's attention or gradient implementation.

To understand the loss, consider predicted outputs `[2, 5]` and targets
`[3, 3]`. The squared differences are `1` and `4`, so:

`MSE = (1 + 4) / 2 = 2.5`.

With a three-by-four output, the real teaching test averages **12** squared
differences instead of two.

## Estimate a gradient without Backward

For one weight `w`, choose a small positive perturbation `ε` and evaluate the
independent loss twice:

`estimatedGradient ≈ (L(w + ε) − L(w − ε)) / ((w + ε) − (w − ε))`.

The denominator uses the **actual stored** floating-point values, because
binary32 does not represent every decimal exactly. The source test uses
`ε = 0.002` and changes one weight at a time, leaving all the others fixed.

Separately, infer the gradient applied by SGD from a real parameter update:

`observedGradient ≈ (oldWeight − newWeight) / learningRate`.

For example, with `oldWeight = 2.0`, `newWeight = 2.2` and learning rate `0.1`,
the observed gradient is `(2.0 − 2.2) / 0.1 = −2`.

Comparing the two routes for all **32 query/key weights** is more persuasive
than inspecting only the final loss. The educational oracle uses a declared
absolute difference threshold of `0.0008`; changing the threshold after a
failure to make the test pass would invalidate the evidence.

## Run the existing Framework qualification

The real test lives in the Framework's native LLM laboratory. Build it with
the already available CMake and CTest targets:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\learning\native-llm\prefix-work" `
    -B ".\build\windows-ucrt64-native-llm-prefix-debug" -G Ninja `
    -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON

cmake --build ".\build\windows-ucrt64-native-llm-prefix-debug" `
    --target umicom-ai-training-rotary-qualification-oracle-test `
    --parallel 2

ctest --test-dir ".\build\windows-ucrt64-native-llm-prefix-debug" `
    -R '^framework\.ai\.training\.rotary_qualification_oracle$' `
    --output-on-failure --no-tests=error
```

A passing independent gradient audit validates **this particular bounded
training exercise**. It does not certify a complete multi-layer language model,
model provenance or an inference acceleration claim.

## Exercises and worked answers

1. **Why is a second call to Backward not an independent reference?** It
   repeats the same algorithm and may repeat the same defect.
2. **A weight moves from 1.0 to 1.1 with learning rate 0.2. What gradient was
   used?** `(1.0 − 1.1) / 0.2 = −0.5`.
3. **If one gradient is outside tolerance, what should the engineer do?**
   Inspect the affected weight, forward calculation, finite-difference step
   and rounding behaviour. Do not silently widen the acceptance tolerance.

For remedial mathematics, revisit [attention and causal masks](../11-maths-for-ai/13-attention-scores-and-causal-masks.md)
and [independent gradient checks](../11-maths-for-ai/14-independent-gradient-checks.md).

**Key point:** Neural optimisation needs independent mathematical evidence,
not merely a plausible loss curve.
