# Mathematics for AI — Unit 8: Attention, Token Positions and KV-Cache Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Companion:** [Illustrated HTML lesson](../../courses/maths-for-ai/lessons/08-attention-and-kv-work.html)

## What you will learn

Attention weighs information from available tokens. It uses three projections: **query (Q)**, **key (K)** and **value (V)**. This lesson shows how dot products, scaling, softmax and weighted sums fit together, and why a key/value cache sometimes saves arithmetic.

## Score two keys

Take `Q = [1,0]`, `K₁ = [1,0]`, `K₂ = [0,1]`, with attention-head width `d = 2`. Scaled dot-product attention uses:

`scoreᵢ = (Q · Kᵢ) / √d`.

The dot products are `1` and `0`. Dividing by `√2 ≈ 1.4142` produces scores approximately `0.7071` and `0`. The scale keeps score magnitudes more manageable as vector width grows.

## Convert scores to weights

Applying softmax to `[0.7071, 0]` gives weights of approximately `[0.6698, 0.3302]`. The weights are nonnegative and sum to one. Now suppose the value vectors are `V₁ = [10,0]` and `V₂ = [0,20]`:

`output = 0.6698 × [10,0] + 0.3302 × [0,20] ≈ [6.698, 6.604]`.

Each value vector contributes according to its attention weight. In causal language modelling, a mask prevents an earlier position from reading information from later positions.

## Why cache keys and values?

When generating one additional token, earlier keys and values can sometimes be reused. In a **growing-prefix** example, the token previously at position zero remains at position zero; earlier positions have not moved and causal attention did not use future tokens. A cache can retain their projections.

For six successively inspected prefixes, the independent calculation performs:

`1 + 2 + 3 + 4 + 5 + 6 = 21 token rows`.

An incremental calculation performs one new row per prefix, or six rows. It avoids `21 − 6 = 15` rows, approximately `71.4%` of the counted rows. That is not necessarily a `71.4%` reduction in wall-clock time: cache allocation, memory traffic, softmax length and operating-system work remain.

By contrast, the existing Umicom decoder's **full rolling window with learned absolute positions** may require all retained positions to be recalculated after each eviction. Reusing stale values in that case changes the mathematics.

## Framework connection

`UmiAiTrainingKvCachePrefill`, `UmiAiTrainingKvCacheAppend` and `UmiAiTrainingKvCacheInspect` belong to Umicom Framework. The prefix work estimator and parity tests qualify their use without creating an independent attention implementation in Bits2Banking.

## Practise and check

**Question A.** A reference computes 100 token rows; a cache computes 75. How many were avoided?  
**Answer.** `25` rows, or `25%` of the reference count.

**Question B.** For nine growing prefixes, find total independent rows and incremental rows.  
**Answer.** `9 × 10 / 2 = 45` independent rows and `9` incremental rows; `36` avoided.

**Question C.** Why might cache eviction invalidate earlier values?  
**Answer.** Token positions or deeper hidden states may change, so the old saved projections no longer represent the same computation.

**Next:** [Reading mathematical formulas in native C23](../../courses/maths-for-ai/lessons/09-reading-maths-in-code.html).
