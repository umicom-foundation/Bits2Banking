# Mathematics for AI — Unit 24: Gradients Through Low-Rank Projections

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Purpose

Understand how changing two small matrices can improve an adapted projection while the original dense matrix stays frozen. The [Transformer adaptation lesson](../10-native-ai/adapt-attention-and-feed-forward-projections.md) uses this principle in the existing C23 training tape.

## 1. Start with a scalar teaching model

Before matrices, use simple numbers. Suppose the output is:

```text
y = xw + (xa)b
```

Here `x=2` is the input, `w=3` is the frozen base weight, and `a` and `b` are the two trainable adapter values. If `a=0.5` and `b=0`, then:

```text
base output = 2 × 3 = 6
adapter correction = (2 × 0.5) × 0 = 0
y = 6
```

The initial adapter leaves the original prediction unchanged.

## 2. Follow the gradient backwards

Let the target be `t=7` and loss be `L=(y−t)²/2`. Initially `y=6`, so `L=(−1)²/2 = 0.5` and `∂L/∂y = y−t = −1`.

Apply the chain rule to the adapter weights:

```text
∂y/∂a = xb
∂y/∂b = xa

∂L/∂a = (y−t) × xb
∂L/∂b = (y−t) × xa
```

With `x=2`, `a=0.5`, `b=0`, the gradients are:

```text
∂L/∂a = −1 × 2 × 0   =  0
∂L/∂b = −1 × 2 × 0.5 = −1
```

The first update changes `b`, not `a`, because the correction's output is initially multiplied by zero. This does **not** mean `a` is permanently unable to train; after `b` changes, its gradient can become nonzero.

## 3. Make one SGD update

Choose learning rate `α=0.1` and subtract `α×gradient` from each trainable parameter:

```text
new a = 0.5 − 0.1×0   = 0.5
new b = 0   − 0.1×(−1) = 0.1
```

Now recompute the complete output:

```text
y = (2 × 3) + (2 × 0.5 × 0.1) = 6.1
L = (6.1 − 7)²/2 = 0.405
```

Loss fell from `0.5` to `0.405` in this one example. That is evidence for a particular training update, not proof that an adapted language model generalises to unseen source code.

## 4. Extend the idea to matrices

For matrices the same expression is:

```text
Y = XW + (XA)B
```

The chain rule uses matrix multiplication and transposes. If `G` is the derivative of loss with respect to `Y`, then the adapter gradients use:

```text
∂L/∂A = Xᵀ G Bᵀ
∂L/∂B = (XA)ᵀ G
```

The dimensions are important. With `X:[N,I]`, `A:[I,r]`, `B:[r,O]` and `G:[N,O]`:

```text
Xᵀ G Bᵀ : [I,N] × [N,O] × [O,r] = [I,r]
(XA)ᵀ G : [r,N] × [N,O]          = [r,O]
```

Those are precisely the shapes of `A` and `B`. The real Framework uses automatic differentiation to calculate the gradients; the equations give learners an independent way to reason about them.

## 5. Why freezing the base matters

The original weight `W` contributes to the forward computation but does not belong in the adapter-only optimiser parameter list. Its values must be unchanged before and after each training step. The Framework's low-rank trainable selector returns `A` and `B` only, and the tape's multi-parameter SGD writer checks a complete candidate update before committing either matrix.

A numerical regression should check both sides: **the new adapter learns** and **the frozen base does not change**.

## Practice

1. Recalculate the scalar example if the target is `5` rather than `7`. What is the initial sign of `∂L/∂b`?
2. Why does `∂L/∂a` start at zero when `b=0`?
3. Check the shape of `∂L/∂B` for `N=8`, `I=128`, `r=8`, `O=256`.
4. Explain why two sets of trainable adapter weights must be updated consistently, rather than publishing only the first successful write.

## Worked answers

1. `y−t = +1`, so `∂L/∂b = +1`.
2. The product `xb` is zero, so the immediate correction is insensitive to `a`.
3. `[8,256]`, the same shape as the adapter-up matrix.
4. A partially updated pair would represent neither the previous model nor the intended complete optimiser step.

**Further study:** [Unit 20 — Matrix chain rule](20-matrix-chain-rule-and-computation-graphs.md) and [Unit 23 — Parameter counts](23-projection-adapters-and-parameter-counts.md).
