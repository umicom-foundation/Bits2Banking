# Mathematics for AI — Unit 134: Count rollover rebuilds for bounded context

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab · **Prerequisite:** Basic arithmetic and an interest in neural networks.

## What will you learn?

Predict full-window fallback frequency from the context capacity.

## Step-by-step calculation

Take context capacity `C=4`, initial prompt length `P=2`, and `G=6` subsequently appended tokens, under a policy that evicts exactly one old token for each overflowing append. The first `C-P=2` appends grow the window without eviction. The remaining `G-(C-P)=4` appends each need a rebased window and therefore a canonical rebuild under the present model policy.

For `G <= C-P`, rollover count is zero. Otherwise, `rollovers=max(0,G-(C-P))`. This simple count assumes no special BOS resets or alternative windowing semantics. It predicts **how often** a fallback occurs, not its measured execution time.

**Notation guide:** `H` = number of attention heads; `T` = valid causal token count; `D` = channels per head; `L` = Transformer layers. The symbols describe *example data*, not the size or performance of an actual deployed model.

## Work it out yourself

**Question:** Capacity 5, prompt length 3, six appends: how many rollovers?

<details>
<summary>Show the worked answer</summary>

`max(0,6-(5-3)) = 4` rollovers.

</details>

## Connect the numbers with native C23

[LLM Lesson 244](../10-native-ai/244-treat-context-rollover-as-a-slow-path-gate.md) explains where this calculation belongs in the planned single-query kernel. The numerical implementation remains Framework-owned; these educational numbers are for checking reasoning, not a substitute for integrated decoder tests.

## Continue learning

[Previous unit](133-prove-prefix-position-invariance.md) · [Browser mathematics path](../../courses/maths-for-ai/single-query-attention-mathematics.html) · [Next unit](135-estimate-attention-arithmetic-and-memory-traffic.md)

*Service to Many Leads to Greatness.*
