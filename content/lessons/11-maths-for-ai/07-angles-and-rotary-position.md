# Mathematics for AI — Unit 7: Angles, Sine, Cosine and Rotary Position

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Companion:** [Illustrated HTML lesson](../../courses/maths-for-ai/lessons/07-angles-and-rotary-position.html)

## What you will learn

A point can be described by two coordinates: `x` measures horizontal position and `y` vertical position. Rotating that point is a way to represent an angle mathematically. Rotary positional encoding (RoPE) uses rotations to introduce token-position information into attention query and key vectors.

## Degrees and radians

One full turn is `360°`, equivalent to `2π` **radians**, where `π ≈ 3.14159`. A quarter turn is therefore `90° = π/2` radians. C mathematical functions such as `sinf` and `cosf` use radians.

For an angle `θ` (theta), a counter-clockwise rotation of `(x,y)` gives:

\[
x' = x\cos\theta - y\sin\theta,\qquad
 y' = x\sin\theta + y\cos\theta.
\]

The prime mark means the coordinate **after** rotation. At `90°`, `cosθ = 0` and `sinθ = 1`. Starting from `(2,0)`:

`x′ = 2×0 − 0×1 = 0`, `y′ = 2×1 + 0×0 = 2`.

The result is `(0,2)`. Its length is still two, but its direction has changed.

## Express the same rule as a matrix

\[
R(\theta) =
\begin{bmatrix}
\cos\theta & -\sin\theta \\
\sin\theta & \cos\theta
\end{bmatrix}.
\]

`R(θ)` is a 2×2 rotation matrix. Its multiplication by `[x, y]ᵀ` produces `[x′, y′]ᵀ`. For an exact rotation, `RᵀR = I`, where `I` is the identity matrix. This is why applying the transpose rotates the result back in the reverse direction.

## How rotary position enters a Transformer

A Transformer builds a **query** and **key** representation from each token. RoPE rotates pairs of coordinates by an angle determined from the token's position and a chosen frequency. The dot product between rotated queries and keys depends on their relative positional relationship. The precise frequency schedule and shape conventions are design choices and must be tested.

Two important distinctions matter:

1. RoPE changes the positional mathematics; it is not merely a cosmetic transformation of the same learned-absolute-position model.
2. Reusing cached keys and values after an attention-context change requires proving every affected hidden state remains valid. Rotary position alone does not make arbitrary cache eviction correct.

## Framework connection

The Umicom Framework contains native rotary position and rotary training modules under `umicom/ai/training/`. Read their public contracts and acceptance tests before comparing RoPE with the original learned-position decoder. A new position policy needs independent numerical parity, checkpoint compatibility decisions and source evidence.

## Practise and check

**Question A.** Rotate `[0,3]` by 90° counter-clockwise.  
**Answer.** `x′=−3`, `y′=0`, so the result is `[−3,0]`.

**Question B.** Convert `180°` to radians.  
**Answer.** `π` radians.

**Question C.** Why must we test gradients as well as forward outputs?  
**Answer.** A rotation may produce correct forward values while a backward implementation uses the wrong sign, ordering or transpose.

**Next:** [Attention, token positions and KV-cache work](08-attention-and-kv-work.md).
