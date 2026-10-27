# Mathematics for AI — Unit 157: Estimate KV read bandwidth floors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

When a decode step must read both K and V for L layers, T stored rows, C channels and four bytes per FP32 element, the minimum dense K/V bytes read are 2*L*T*C*4 before considering cache effects.

## 2. Fully worked calculation

With L=3, T=100, C=1024, the model reads about 2*3*100*1024*4=2,457,600 bytes of K/V projections per step. An ideal 100 GB/s memory stream would transfer that in about 24.6 microseconds, ignoring all other work.

## 3. Practise independently

**Question:** Compute bytes for L=2, T=32, C=256.

<details>
<summary>Show the worked answer</summary>

2×2×32×256×4 = 131,072 bytes.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[156 — Calculate grouped-query cache ratios](156-calculate-gqa-cache-head-ratio.md) · [158 — Bound reused prefix validity](158-bound-reused-prefix-validity.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
