# Mathematics for AI — Unit 156: Calculate grouped-query cache ratios

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

For Hq query heads and Hkv K/V heads of equal head width d, KV bytes per retained token are proportional to 2*Hkv*d (keys plus values). MHA commonly uses Hkv=Hq; grouped-query attention uses Hkv<Hq.

## 2. Fully worked calculation

With Hq=8 and Hkv=2, the K/V head count and same-width cache payload are 2/8=1/4 of the eight-head arrangement. The query heads do not shrink.

## 3. Practise independently

**Question:** For Hq=16 and Hkv=4, what is the relative KV head count?

<details>
<summary>Show the worked answer</summary>

4/16=1/4.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[155 — Track window-rollover position indices](155-track-window-rollover-position-indices.md) · [157 — Estimate KV read bandwidth floors](157-estimate-kv-read-bandwidth-floor.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
