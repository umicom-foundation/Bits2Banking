# Mathematics for AI — Unit 4: Matrices, Shapes and Multiplication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## What you will learn

Read a matrix by its rows and columns, calculate a matrix product one cell at a time, check shape compatibility, and understand the meaning of a transpose.

## 1. A matrix is a rectangular table

A **matrix** arranges numbers into rows and columns. For example,

**Calculation:** `A=[[1, 2], [3, 4]]`

has two rows and two columns; its shape is **2 × 2**. In model code, a matrix may hold learnable weights, activations or another organised set of numbers. Its shape is part of its meaning: it determines which operations are defined.

## 2. Multiply one row by one column

Let

**Calculation:** `A=[[1, 2], [3, 4]], B=[[2, 0], [1, 2]].`

For the entry in row 1, column 1 of `AB`, take row 1 of `A` and column 1 of `B`. Multiply corresponding values and add:

**Calculation:** `1×2+2×1=4.`

Repeat for the other cells:

| Output cell | Calculation | Result |
| --- | --- | ---: |
| Top left | `1×2+2×1` | 4 |
| Top right | `1×0+2×2` | 4 |
| Bottom left | `3×2+4×1` | 10 |
| Bottom right | `3×0+4×2` | 8 |

Therefore

**Calculation:** `AB=[[4, 4], [10, 8]].`

Matrix multiplication is generally **not commutative**. In this example,

**Calculation:** `BA=[[2, 4], [7, 10]],`

which differs from `AB`. The order of transformations matters in a neural network.

## 3. The inner dimensions must match

If `A` has shape `m × n` and `B` has shape `n × p`, then `AB` has shape `m × p`. The two inner `n` dimensions match because each row of `A` must contain the same number of entries as each column of `B`.

For example, **2 × 3** multiplied by **3 × 4** produces **2 × 4**. Attempting **2 × 3** multiplied by **2 × 4** is invalid under ordinary matrix multiplication: the inner dimensions 3 and 2 do not match.

This is the mathematical reason why native tensor libraries must validate shapes *before* accessing buffers.

## 4. Transpose: swap rows and columns

The transpose `Aᵀ` exchanges row and column positions:

**Calculation:** `Aᵀ=[[1, 3], [2, 4]].`

A matrix of shape `r × c` becomes `c × r` when transposed. Transposes occur in gradient propagation and in many projection formulas. They are not the same operation as changing a matrix's order in memory; code must respect the documented tensor layout.

## 5. Practice

1. Predict the shape of **5 × 3** multiplied by **3 × 2**.
2. Is a product of **4 × 5** and **4 × 2** defined? Why?
3. Calculate `[1,2] [3,4]ᵀ` as a one-row-by-one-column matrix product.
4. Find the transpose of `C=[[2, 5, 7], [1, 0, -1]]`.

<details>
<summary>Show worked answers</summary>

1. **5 × 2**; the inner dimensions are both 3.
2. **No**, because the inner dimensions 5 and 4 differ.
3. `1×3+2×4=11`, a 1 × 1 matrix.
4. `Cᵀ=[[2, 1], [5, 0], [7, -1]]`, with shape **3 × 2**.

</details>

## 6. Check your understanding

Describe how a matrix shape check can prevent a memory error in native code. Then explain why multiplying two matrices in reverse order may change the result even when both products are valid.

**Companion reading:** [Illustrated Unit 4](../../courses/maths-for-ai/lessons/04-matrices-and-shapes.html) · [Previous: Vectors](03-vectors-and-dot-products.md) · [Next illustrated unit: Probability, Softmax and Loss](../../courses/maths-for-ai/lessons/05-probability-softmax-and-loss.html).
