# Mathematics for AI — Unit 155: Track window-rollover position indices

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

For context size W, a full window [x0,...,x(W−1)] and incoming xW becomes [x1,...,xW]. Surviving tokens move from indices 1,...,W−1 to 0,...,W−2.

## 2. Fully worked calculation

For W=4, B moves from position 1 in [A,B,C,D] to position 0 in [B,C,D,E]. Learned absolute embeddings make the old and new B representations different.

## 3. Practise independently

**Question:** If W=7, how many surviving tokens change position on rollover?

<details>
<summary>Show the worked answer</summary>

W−1 = 6 surviving tokens.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[154 — Compute absolute-plus-relative error](154-compute-absolute-plus-relative-error.md) · [156 — Calculate grouped-query cache ratios](156-calculate-gqa-cache-head-ratio.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
