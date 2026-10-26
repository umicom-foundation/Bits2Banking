# Unit 63 — Prefill and decoding work, counted carefully

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

A model with `L` Transformer layers and context `C` that recalculates a whole context for `G` generated tokens requests `L × C × G` layer-token rows. If `L=3`, `C=8` and `G=6`, the result is `3 × 8 × 6 = 144`. This count excludes attention dot-product lengths, embedding lookup, logits projection and memory transfers.

## Where this matters

A hypothetical retained cache that processes eight prefill tokens and five later appended tokens would instead request `(8 + 5) × 3 = 39` layer-token rows **if the cache were mathematically valid**. The current Umicom stacked decoder does not implement that optimisation. Do not report `39` as observed work.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** Compute the full-context work for four layers, context eight and five generated tokens.

<details><summary>Reveal the worked answer</summary>

`4 × 8 × 5 = 160` layer-token rows.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
