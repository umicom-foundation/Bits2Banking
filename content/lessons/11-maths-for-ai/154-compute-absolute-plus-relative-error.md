# Mathematics for AI — Unit 154: Compute absolute-plus-relative error

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

Element-wise parity may use |x−y| ≤ atol + rtol*|y|. The bound is evaluated for each reference value, with an explicit decision whether equality is accepted.

## 2. Fully worked calculation

For reference=10, candidate=10.00002, atol=0.00001 and rtol=0.000002, the allowable difference is 0.00001+0.00002=0.00003, so 0.00002 passes.

## 3. Practise independently

**Question:** With reference 0 and candidate 0.00004, atol=0.00001, rtol=0.1, does it pass?

<details>
<summary>Show the worked answer</summary>

No. The relative term vanishes at reference zero, leaving a bound of 0.00001.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[153 — Calculate operator scratch bytes](153-calculate-operator-scratch-bytes.md) · [155 — Track window-rollover position indices](155-track-window-rollover-position-indices.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
