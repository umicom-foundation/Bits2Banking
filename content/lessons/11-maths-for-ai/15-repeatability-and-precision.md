# Mathematics for AI — Unit 15: Repeatability, Precision and Evidence

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning outcome

Learn why a result can be numerically correct without matching every floating-point bit, how to declare tolerances, and how to distinguish training progress, computation, memory and model quality.

## 1. Real numbers and stored numbers differ

Mathematics permits numbers with arbitrarily many digits. Typical training arrays use **float32**, which allocates 32 bits to a floating-point representation. Decimal `0.1` cannot be stored exactly in binary32, so repeated arithmetic may involve small rounding errors. Different summation orders or instruction choices can produce slightly different final values even when they implement the same mathematical formula.

Exact byte equality remains appropriate for hashes, identifiers and immutable checkpoint bytes. Approximate equality may be appropriate for independently calculated floats—but only under a justified and documented bound.

## 2. Two-part numerical tolerance

A useful check is:

`|actual − reference| ≤ absTol + relTol × |reference|`

`|x|` means absolute value; `absTol` is a fixed allowed error; `relTol` is a fraction of the reference magnitude. The two terms help with values near zero and values far from zero.

Example: `reference = 0.010000`, `actual = 0.010002`, `absTol = 0.000001` and `relTol = 0.001`.

The observed error is `0.000002`. The allowed error is `0.000001 + 0.001 × 0.010000 = 0.000011`. Since `0.000002 ≤ 0.000011`, this result passes.

A tolerance is not a permission to ignore `NaN`, infinity, shape mismatches or uninitialised memory. These must be rejected separately.

## 3. Repeatability and reproducibility

**Repeatability** asks whether the same run under equivalent inputs and environment reproduces the result. **Reproducibility** asks whether another suitably documented environment can independently reproduce the finding. For AI, the record should identify model/checkpoint bytes, dataset version, training/evaluation split, random seed, optimiser configuration, compiler and test procedure.

Equal seeds alone do not guarantee equality when threads, floating-point reductions, unavailable device libraries or nondeterministic kernels differ.

## 4. Measurements answer different questions

| Measurement | What it supports | What it does not establish |
|---|---|---|
| Token rows calculated | An algorithm's counted work | Elapsed wall time |
| CPU seconds | Process CPU consumption | User-visible latency in every workload |
| Peak tape-owned bytes | Maximum tracked native graph allocation | Whole-process resident memory |
| Training loss | Fit to a declared training objective | Generalisation to unseen tasks |
| Held-out loss | Fit to the selected unseen dataset | Comprehensive safety or professional suitability |
| Checkpoint SHA-256 | Exact content identity | Authenticity of the publisher |

A model's test data must be independently governed; lowering training loss alone can reflect memorisation.

## 5. Rotary position and relative offsets

In ideal rotary position embeddings, a corresponding shift of both positions preserves their *relative difference*. Positions 5 and 3 differ by 2; positions 15 and 13 also differ by 2. Under the appropriate rotation construction, the ideal query–key dot product depends on this difference. Finite floating-point calculations still require tolerance checks. The property does **not** mean every multi-layer cache can be reused safely after removing old context.

## 6. Review the complete evidence chain

Before accepting a reported improvement: verify output parity, compare held-out quality, ensure the same source and checkpoint, observe wall-clock timing across repeated runs, and inspect memory accounting. A native Framework training or inference test should report the actual executable result; a training plan or narrative is not itself execution evidence.

## Practice and worked answer

**Question:** `reference=0.50`, `actual=0.5003`, `absTol=0.0001`, `relTol=0.0002`. Does the comparison pass?

**Answer:** Observed error `= 0.0003`. Allowed error `= 0.0001 + 0.0002 × 0.50 = 0.0002`. Since `0.0003 > 0.0002`, **it fails**.

Use the [illustrated HTML lesson](../../courses/maths-for-ai/lessons/15-repeatability-and-precision.html) for diagrams and additional exercises. See [finite differences](12-finite-differences-and-floating-point.md) and [evidence thresholds](19-evidence-thresholds-and-uncertainty.md).
