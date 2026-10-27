# Mathematics for AI — Unit 203: Index layer-major stored projections

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Compute the correct offset without mixing layers and token positions.

## Step-by-step derivation

For full-capacity storage `[layer][token][channel]` with context length `T` and channel width `C`, the flat offset is `(layer × T + token) × C + channel`. For `T=4`, `C=8`, layer 1, token 2, channel 3 gives `(1×4+2)×8+3=51`. If keys occupy a packed prefix of `L×T×C` scalars, the corresponding value offset adds exactly that prefix. It is the store, not the pool, that should own and interpret this layout.

## Check your understanding

**Exercise:** Find the offset of layer 0, token 3, channel 7 for `T=4,C=8`.

<details><summary>Show the worked solution</summary>

31, because `(0×4+3)×8+7=31`.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](202-check-multiplication-before-it-overflows-size-t.md) · [Next unit](204-write-a-failure-atomic-state-invariant.md) · [Browser unit](../../courses/maths-for-ai/lessons/203-index-layer-major-stored-projections.html)

*Service to Many Leads to Greatness.*
