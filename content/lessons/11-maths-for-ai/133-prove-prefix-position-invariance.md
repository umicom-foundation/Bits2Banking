# Mathematics for AI — Unit 133: Prove prefix-position invariance for appends

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Recognise when previously cached token-position pairs stay unchanged.

## Step-by-step calculation

With an absolute-position model, a cache append is eligible for reuse only if the old positions and the model state remain unchanged. Suppose prefix tokens are `(A@0,B@1)` and a new token `C@2` arrives. Existing tokens still have positions 0 and 1; a causal decoder also prevents token `C` from affecting earlier outputs. This is the **unchanged-position append** case.

If instead the system prepends `X@0` and moves old tokens to `A@1,B@2`, the old cached projections no longer represent those token-position pairs. Equality of token byte strings alone does not prove equality of learned hidden states.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** Can a cached `B@1` safely be reused as `B@0` in a learned absolute-position model?

<details>
<summary>Show the worked answer</summary>

Not without independent proof. Its positional embedding and potentially its attention history differ.

</details>

## Connect the numbers with native C23

[LLM Lesson 239](../10-native-ai/239-keep-learned-position-embeddings-consistent.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](132-calculate-cache-and-scratch-memory.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](134-count-rollover-rebuilds-for-bounded-context.md)

*Service to Many Leads to Greatness.*
