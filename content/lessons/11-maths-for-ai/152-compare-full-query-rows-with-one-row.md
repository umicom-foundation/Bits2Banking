# Mathematics for AI — Unit 152: Compare full-query rows with one row

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

The canonical all-rows causal attention computes T query rows for a T-token window. The incremental one-query path computes one. Across L layers, row work changes from L*T to L for a growing-prefix append; other work remains.

## 2. Fully worked calculation

For L=3 and T=5 the query-row count changes 15→3, a reduction of 12 rows. Keys visited by the newest query still include all five positions per head.

## 3. Practise independently

**Question:** For L=2 and T=9, how many query rows are avoided?

<details>
<summary>Show the worked answer</summary>

2×9−2=16 query rows.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[151 — Count single-query head operations](151-count-single-query-head-operations.md) · [153 — Calculate operator scratch bytes](153-calculate-operator-scratch-bytes.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
