# Mathematics for AI — Unit 158: Bound reused prefix validity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

Two inference requests can reuse a cached prefix only when the model identity, token IDs, positional semantics and causal history are identical for the reused span. Equal token counts alone are not sufficient.

## 2. Fully worked calculation

Prompt P=[7,11,13] and Q=[7,11,14] share a two-token exact prefix. Under unchanged absolute positions, at most two leading rows are direct reuse candidates; the third differs.

## 3. Practise independently

**Question:** What is the longest common leading prefix of [1,2,3,4] and [1,2,5,4]?

<details>
<summary>Show the worked answer</summary>

Two tokens.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[157 — Estimate KV read bandwidth floors](157-estimate-kv-read-bandwidth-floor.md) · [159 — Distinguish logit and token agreement](159-distinguish-logit-and-token-agreement.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
