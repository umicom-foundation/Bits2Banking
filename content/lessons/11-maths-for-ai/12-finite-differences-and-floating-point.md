# Mathematics for AI — Unit 12: Finite Differences and Floating-Point Tests

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisites:** [Derivatives](06-derivatives-and-chain-rule.md) and [reading mathematics in C23](09-reading-maths-in-code.md).

## Learning objectives

Approximate an analytical gradient with independent function evaluations, choose a useful perturbation, compare finite floating-point results against declared tolerances and distinguish mathematical parity from runtime performance.

## 1. Why test a derivative twice?

A reverse-mode differentiation engine can return a plausible value even when a gradient is wrong. A useful independent check perturbs one parameter and evaluates the loss above and below its current value. This is called a **central finite difference**:

`gradient ≈ (L(w + ε) − L(w − ε)) / (2ε)`.

`L` is loss, `w` the parameter under test, and `ε` (epsilon) a small positive distance. The two function evaluations do not ask the automatic-gradient system for its answer.

## 2. Calculate every part

Let `L(w) = (w − 2)²`, test at `w = 1`, and choose `ε = 0.01`.

- `w + ε = 1.01` gives `L(1.01) = (−0.99)² = 0.9801`.
- `w − ε = 0.99` gives `L(0.99) = (−1.01)² = 1.0201`.
- The numerator is `0.9801 − 1.0201 = −0.0400`.
- The denominator is `2 × 0.01 = 0.02`.

The numerical derivative is `−0.0400 / 0.02 = −2`. Differentiating symbolically gives `2(w − 2) = −2` at `w = 1`. They agree in this example.

## 3. A numerical tolerance must be declared in advance

A practical check compares `|actual − reference|` with a permitted tolerance. For example, `0.50002` differs from `0.50000` by `0.00002`. It passes a tolerance of `0.00005` but fails `0.00001`.

```c
#include <math.h>

float actual = 0.50002F;
float reference = 0.50000F;
float tolerance = 0.00005F;
int pass = isfinite(actual) && isfinite(reference) &&
           fabsf(actual - reference) <= tolerance;
```

For problems spanning different scales, an absolute-and-relative condition can be useful:

`|actual − reference| ≤ atol + rtol × |reference|`.

`atol` is absolute tolerance; `rtol` is relative tolerance. The values must be justified by the numerical method and expected accuracy, not adjusted after a failing test.

## 4. Why not make epsilon arbitrarily small?

In finite-precision arithmetic, two nearly identical loss evaluations may round to the same stored value. Their subtraction can then be dominated by rounding. A very large epsilon has the opposite problem: it averages over too wide an interval and no longer captures a local slope. Report epsilon, data type and numerical method alongside results.

Never use a tolerance for exact byte identities, checkpoint digests, account identifiers or immutable sequence counters. Exact objects need exact checks.

## 5. Correctness is not performance

A KV cache may compute fewer token rows while using more memory or additional copying. Equal sampled tokens may still conceal different probability scores. Measure numerical parity, workload counters, peak memory, CPU time and wall-clock time as **different evidence categories**.

## Practise

**Exercise A.** If the reference is `0.75` and actual value `0.75008`, does it pass tolerance `0.0001`? What about `0.00005`?  
**Answer.** Difference `0.00008`; it passes the first and fails the second.

**Exercise B.** Why is a comparison of two KV-cache schedules weaker than comparing with the canonical decoder?  
**Answer.** Both cache schedules may share the same underlying defect; the canonical decoder exercises a different implementation path.

**Further study:** [Illustrated Unit 12](../../courses/maths-for-ai/lessons/12-finite-differences-and-floating-point.html) · [Canonical decoder qualification](../10-native-ai/71-qualify-canonical-decoder-kv-parity.md).
