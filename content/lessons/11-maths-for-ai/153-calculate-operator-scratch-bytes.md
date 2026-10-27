# Mathematics for AI — Unit 153: Calculate operator scratch bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

A simple forward kernel uses T double-precision scores, T FP32 probabilities and C FP32 output candidates. Requested scratch payload is 8T+4T+4C bytes, excluding allocator metadata and tape nodes.

## 2. Fully worked calculation

For T=6 and C=8, scratch payload is 48+24+32=104 bytes. This is not the complete model or process memory footprint.

## 3. Practise independently

**Question:** How much requested scratch is used for T=10, C=16?

<details>
<summary>Show the worked answer</summary>

8×10 + 4×10 + 4×16 = 184 bytes.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[152 — Compare full-query rows with one row](152-compare-full-query-rows-with-one-row.md) · [154 — Compute absolute-plus-relative error](154-compute-absolute-plus-relative-error.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
