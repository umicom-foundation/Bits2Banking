# Mathematics for AI — Unit 205: Count projected rows at a full-window rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Basic arithmetic and the preceding mathematics units.

## Learning objective

Distinguish incremental append work from complete multi-layer recomputation.

## Step-by-step derivation

With `L` layers and context length `T`, an unchanged-position append projects one new K/V row per layer: `L` token-layer rows. A learned-position rollover requires all `L×T` rows to be recomputed by the canonical decoder. For `L=3,T=8`, append is 3 token-layer rows and rollover is 24. A ring-buffer shift is not a valid shortcut if absolute positional embeddings changed.

## Check your understanding

**Exercise:** What are the two work counts for `L=2,T=6`?

<details><summary>Show the worked solution</summary>

Two token-layer rows for append; twelve for full-context rollover.

</details>

## Native C23 connection

Use the Framework's existing checked `InferenceMemoryPlan`, `StackedKvStore` and `StackedKvPool` contracts. Arithmetic estimates do not themselves prove safe allocation, neural accuracy or measured latency.

## Continue learning

[Previous unit](204-write-a-failure-atomic-state-invariant.md) · [Next unit](206-estimate-the-limits-of-shared-prefix-savings.md) · [Browser unit](../../courses/maths-for-ai/lessons/205-count-projected-rows-at-a-full-window-rollover.html)

*Service to Many Leads to Greatness.*
