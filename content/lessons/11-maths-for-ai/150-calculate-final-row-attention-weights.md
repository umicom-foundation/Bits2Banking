# Mathematics for AI — Unit 150: Calculate final-row attention weights

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

For scores a and b, stable softmax computes p_a = exp(a-m)/(exp(a-m)+exp(b-m)), with m=max(a,b). The first score is not automatically given weight 1.

## 2. Fully worked calculation

With scores (0, ln 3), m=ln 3. Weights are (1/4,3/4). With values (2,6), the weighted output is (1/4)*2+(3/4)*6=5.

## 3. Practise independently

**Question:** Scores are (ln 2, 0). What are the two probabilities?

<details>
<summary>Show the worked answer</summary>

2/3 and 1/3.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[149 — Locate the newest query row](149-locate-the-newest-query-row.md) · [151 — Count single-query head operations](151-count-single-query-head-operations.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
