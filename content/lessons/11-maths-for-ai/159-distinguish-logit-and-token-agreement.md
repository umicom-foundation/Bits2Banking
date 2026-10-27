# Mathematics for AI — Unit 159: Distinguish logit and token agreement

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

Greedy token agreement checks argmax(logits). A full-logit comparison checks all entries and usually yields stronger evidence. Sampling also depends on probability normalisation, nucleus selection and PRNG state.

## 2. Fully worked calculation

Vectors [8,7,1] and [8,0,7] share greedy ID 0 but differ in two other coordinates. A top-p sampler may choose different sets of candidates even with the same seed.

## 3. Practise independently

**Question:** Can a 100% greedy agreement score prove all logits are equal?

<details>
<summary>Show the worked answer</summary>

No. Argmax discards all non-winning scores.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[158 — Bound reused prefix validity](158-bound-reused-prefix-validity.md) · [160 — Construct an integrated evidence matrix](160-construct-the-integrated-evidence-matrix.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
