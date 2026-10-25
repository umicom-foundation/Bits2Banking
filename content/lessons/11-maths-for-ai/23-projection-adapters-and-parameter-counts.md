# Mathematics for AI — Unit 23: Projection Adapters and Parameter Counts

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Purpose

Learn to calculate the shapes and parameter counts of a low-rank adapter before writing C23. This unit accompanies [native Transformer projection adaptation](../10-native-ai/adapt-attention-and-feed-forward-projections.md). No advanced mathematics is required: only multiplication, addition and a basic understanding of matrices.

## 1. What does a dense projection do?

A row of `I` input values is multiplied by a matrix containing `I` rows and `O` columns. The result contains `O` output values. The full weight matrix has:

```text
denseParameters = I × O
```

For four inputs and six outputs, the dense matrix contains `4 × 6 = 24` values. Their units are *parameters*, not bytes. If each value occupies four bytes, the weight data occupy `24 × 4 = 96` bytes, excluding graph and storage metadata.

## 2. Use two narrow matrices instead

A low-rank adapter adds a trainable correction without replacing the dense weights. Choose a small rank `r`:

```text
A: [I, r]       B: [r, O]
X: [N, I]       XA: [N, r]
(XA)B: [N, O]
```

The adapter has `I×r + r×O = r×(I+O)` trainable numbers. With `I=4`, `O=6`, `r=2`, this is `8+12=20`. The original 24 dense values are retained but need not be updated during adapter training.

Notice that the example saves only four trainable values compared with training the entire dense matrix. For narrow toy networks, low rank may provide little benefit; its practical advantage grows with wider projections.

## 3. A more realistic numerical comparison

Suppose a projection has 128 inputs, 256 outputs and rank 8:

```text
Full dense matrix:       128 × 256      = 32,768 weights
Adapter down matrix:     128 × 8        =  1,024 weights
Adapter up matrix:         8 × 256      =  2,048 weights
Total adapter trainables:                =  3,072 weights
```

The adapter has `3,072 / 32,768 = 0.09375`, or **9.375%** as many *trainable* parameters as that one dense projection. This does not mean the total model occupies 9.375% of its previous memory: the frozen dense weights still exist. Optimiser moments, gradients and temporary activations add further memory costs.

## 4. Why a zero-initialised matrix matters

Write the adapted result as `Y = XW + (XA)B`. At creation, `B` is zero. The correction `(XA)B` is then zero and the initial output is `XW`. This is a useful regression invariant: an untrained adapter must not unexpectedly alter the established model.

Once training changes `B`, the correction can become nonzero. Gradients may subsequently update both narrow matrices. All of those calculations remain inside the Framework training tape; educational applications should use the public API rather than implement an independent neural engine.

## Practice

1. Calculate the dense parameter count when `I=64`, `O=64`.
2. Calculate adapter parameters when `I=64`, `O=64`, `r=4`.
3. Explain why a small adapter count does not mean the frozen dense weights can be discarded.
4. What is the output shape of an `[8,128]` input multiplied by a `[128,8]` adapter-down matrix and then an `[8,256]` adapter-up matrix?

## Worked answers

1. `64×64 = 4,096`.
2. `64×4 + 4×64 = 512`, which is **12.5%** of the dense weight count.
3. The correction adds to the original dense result; inference still needs the original weights.
4. The intermediate shape is `[8,8]`; the final correction shape is `[8,256]`.

**Further study:** [Matrices and shapes](04-matrices-and-shapes.md), [Gradient descent](10-gradient-descent-and-learning-rate.md) and [Unit 24 — Gradients through a low-rank residual](24-gradients-through-low-rank-projections.md).
