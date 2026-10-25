# Lesson 81 — Rotary position mathematics from first principles

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation owner:** Umicom Framework (C23)

## Learning objectives

Explain rotary positional encoding (RoPE), calculate one two-dimensional rotation, understand relative-position behaviour and identify why new positional mathematics cannot be applied to old learned-absolute checkpoints without qualification.

## 1. The rotation of a pair

A query or key vector contains numbers used to calculate attention. RoPE rotates adjacent channel pairs by an angle determined by their token position. For input `(x, y)` and rotation angle `θ` (theta):

- `x' = x × cos(θ) − y × sin(θ)`
- `y' = x × sin(θ) + y × cos(θ)`

The rotation preserves the length `√(x² + y²)` in exact arithmetic. For `(1, 0)` rotated by one radian, the result is approximately `(0.540302, 0.841471)`.

The existing research kernel selects the angle for pair **j** at absolute position **p** using an even rotary width **d** and frequency base **b**:

`θ(p, j) = p × b^(−2j/d)`.

For `d = 4`, `b = 10,000`, pair zero rotates by `p` radians and pair one by `p/100`. Channels outside the configured rotary width remain unchanged.

## 2. Why relative separation is useful

If both the query and key positions shift by the same amount, their separation stays constant. Positions `(6, 2)` and `(106, 102)` both differ by four. Ideal RoPE dot products depend on the relative difference, so both pairs yield the same attention score up to numerical rounding.

This concerns the **query/key rotation**, not necessarily every hidden state in a deep Transformer. Later-layer hidden states can depend on old context that has since been removed. Reusing those states after eviction requires independent validation.

## 3. Use the Framework's native API

```c
#include "umicom/ai/training/rotary_position.h"

const UmiAiTrainingRotaryConfig config = {4U, 4U, 10000.0};
const float query[4] = {1.0F, 0.0F, 0.2F, 0.7F};
float rotated[4] = {0};

UmiStatus status = UmiAiTrainingRotaryRotate(
    &config, query, 4U, 3U, rotated, 4U);
```

The configuration here rotates four channels. This API is an **isolated mathematical component**, not a Transformer checkpoint converter. Its public contract requires finite inputs, bounded positions and an even rotary width. It can safely rotate in place with staging.

## 4. Exercise

Rotate the pair `(0, 1)` by **π/2** radians. Because `cos(π/2) = 0` and `sin(π/2) = 1`, the result is `(−1, 0)`. Its length is still one. Now explain why replacing an existing model's learned positional embeddings with rotations would change its training and inference equations.

**Takeaway:** a new position encoding requires its own model identity, independently trained or qualified parameters and explicit checkpoint compatibility rules.

[Illustrated lesson](../../courses/llm-from-scratch/lessons/81-introduce-rotary-position-mathematics.html) · [Mathematics for AI: rotary position](../11-maths-for-ai/07-angles-and-rotary-position.md) · [Next](82-prove-single-block-rotary-kv-reuse.md)
