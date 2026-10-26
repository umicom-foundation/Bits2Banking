# Unit 64 — Why the attention score table grows quadratically

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

For one sequence of `T` tokens, a full attention-score table contains `T × T` positions. With `T=8` that is 64 locations per head, although causal masking only allows a lower triangle to influence predictions. The allowed triangle contains `T(T+1)/2` entries: for eight tokens, `8×9/2=36`.

## Where this matters

A causal mask prevents a query at position `t` from reading keys at later positions. It does not mean a particular implementation necessarily allocates only the 36 allowed scores; some kernels materialise the full 64-position table. Distinguish mathematical support from memory allocation.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** For ten tokens, how many full score locations and allowed causal positions exist?

<details><summary>Reveal the worked answer</summary>

The full table contains `10×10=100` entries; the lower triangle has `10×11/2=55` allowed positions.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
