# Unit 68 — Combine numerical gates without confusing their meanings

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

Suppose the reference held-out cross-entropy is 0.61 and a candidate returns 0.64. The absolute increase is `0.64−0.61=0.03`. If the maximum allowed increase is 0.04, the loss gate passes. If candidate accuracy is 0.58 and the minimum is 0.60, the combined policy fails.

## Where this matters

A successful comparison operation may reasonably report `candidateAccepted = false`. That is different from an API error, such as an invalid target token, non-finite score or mismatched dataset. A content digest establishes matching bytes, not training rights or publisher authenticity.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** A candidate increases loss from 0.50 to 0.56 when the permitted increase is 0.05. Should it pass that loss gate?

<details><summary>Reveal the worked answer</summary>

No. The increase is `0.06`, above the allowed `0.05`.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
