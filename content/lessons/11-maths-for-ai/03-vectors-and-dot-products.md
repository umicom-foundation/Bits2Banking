# Mathematics for AI — Unit 3: Vectors, Coordinates and Dot Products

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## What you will learn

Read a vector, add two vectors of matching size, compute a dot product by hand, and distinguish a similarity-related score from a factual claim.

## 1. A vector is an ordered list

A computer model works with numerical representations. A simple vector is an **ordered list of numbers**, such as

**Calculation:** `v=[1,2].`

This vector has **two coordinates**, also called components. The first entry is 1 and the second is 2. Swapping them produces `[2,1]`, a different vector. The ordering matters because each position participates in a corresponding mathematical operation.

For another vector `w=[3,4]`, addition pairs corresponding entries:

**Calculation:** `v+w=[1+3, 2+4]=[4,6].`

Vectors must have the same dimension to be added coordinate by coordinate.

## 2. The dot product: multiply, then add

The dot product of two vectors of dimension `n` is

**Calculation:** `v·w=v1*w1 + v2*w2 + ... + vn*wn.`

The symbol `Σ` means “add up”. The subscript `i` identifies a matching position. For two coordinates, the formula is simply `v_1w_1+v_2w_2`.

With `v=[1,2]` and `w=[3,4]`:

**Calculation:** `v·w=(1×3)+(2×4)=3+8=11.`

Notice that the result is **one number**, not a new two-element vector.

## 3. What a negative coordinate does

Let a query vector be `q=[2,1]` and a key vector `k=[3,-1]`. Their dot product is

**Calculation:** `q·k=(2×3)+(1×-1)=6-1=5.`

A negative component can reduce the score. The computation is arithmetic; a positive score is not automatically evidence that a generated statement is correct.

## 4. Dimension and geometric magnitude

The **dimension** of `[1,2]` is 2, because there are two coordinates. Its Euclidean **magnitude** is

**Calculation:** `magnitude(v)=√(1² + 2²)=√5≈2.236.`

This distinction matters: the word “length” may mean the number of entries in an array or its geometric magnitude. Always say which one you intend. A vector can have dimension 128 and a magnitude much smaller than 128.

## 5. Connection to attention and retrieval

A transformer produces query and key vectors from learned representations. A dot product between a query and a key helps calculate an **attention score**. Those scores are normally scaled and converted into weights before values are combined. An embedding-based retrieval system can also compare vectors, but the outcome depends on the encoder, normalisation, data and comparison measure. Similarity does not establish source reliability.

## 6. Practice

1. Add `[3,-2]` and `[-1,5]`.
2. Find the dot product of `[2,-1,3]` and `[4,0,-2]`.
3. Calculate the magnitude of `[3,4]`.
4. Can the dot product of `[1,2]` and `[3,4,5]` be computed by this definition? Explain.

<details>
<summary>Show worked answers</summary>

1. `[3+(-1),-2+5]=[2,3]`.
2. `2 × 4 + (-1) × 0 + 3 × (-2) = 8 + 0 - 6 = 2`.
3. `√(3² + 4²) = √25 = 5`.
4. **No:** the vectors have different dimensions, so there is no one-to-one pairing for all coordinates.

</details>

## 7. Check your understanding

Explain why `v·w` is one number but `v+w` is a vector. Then describe why a high attention score cannot substitute for independent verification of a model's output.

**Companion reading:** [Illustrated Unit 3](../../courses/maths-for-ai/lessons/03-vectors-and-dot-products.html) · [Previous: Variables and Functions](02-variables-and-functions.md) · [Next: Matrices and Shapes](04-matrices-and-shapes.md).
