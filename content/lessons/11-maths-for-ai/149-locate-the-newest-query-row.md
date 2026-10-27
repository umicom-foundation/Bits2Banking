# Mathematics for AI — Unit 149: Locate the newest query row

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Arithmetic, vectors and basic Transformer terminology

**Learning objective:** Understand one quantitative check used to evaluate incremental decoder correctness or efficiency.

## 1. The mathematical relationship

For a retained prefix of T rows and C channels, the newest dense query occupies the row-major offset T*C in an old (T+1)×C query matrix. The single-query kernel instead receives only C floats.

## 2. Fully worked calculation

If T=3 and C=4, the old newest row begins at index 12 and occupies indices 12–15. Its compact representation is 4 floats rather than the original 16-float matrix.

## 3. Practise independently

**Question:** What is the last-row offset when T=5 and C=8?

<details>
<summary>Show the worked answer</summary>

5×8 = 40 float elements.

</details>

## 4. Application

The associated native inference curriculum uses these calculations to distinguish exact shape and index invariants from floating-point tolerances, estimated memory usage and genuinely observed performance. Numerical counts must be checked against the model's actual configuration.

## Continue learning

[Mathematics Unit 148](148-separate-ttft-tpot-and-throughput.md) · [150 — Calculate final-row attention weights](150-calculate-final-row-attention-weights.md) · [HTML mathematics route](../../courses/maths-for-ai/integrated-attention-mathematics.html)
