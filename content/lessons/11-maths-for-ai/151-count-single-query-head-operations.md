# Mathematics for AI — Unit 151: Count single-query head operations

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

For H heads of width d and T key positions, the dot products use H*T*d = T*C multiply-accumulate pairs, where C=H*d. The value-weighted sum has another T*C pairs.

## 2. Fully worked calculation

With T=4, H=2 and d=3, C=6, giving 24 Q×K pairs and 24 weighted-value pairs; the number of scored (head,key) pairs is H*T=8.

## 3. Practise independently

**Question:** What is the Q×K pair count for T=7, H=4 and d=2?

<details>
<summary>Show the worked answer</summary>

7×4×2 = 56 pairs.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[150 — Calculate final-row attention weights](150-calculate-final-row-attention-weights.md) · [152 — Compare full-query rows with one row](152-compare-full-query-rows-with-one-row.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
