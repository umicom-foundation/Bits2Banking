# Unit 65 — Distinguish saved activations from stored weights

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

A matrix holding `T` token rows of `C` float32 channels stores `T × C × 4` raw bytes. An example with `T=12` and `C=16` holds `12×16×4=768` bytes. Retaining one such matrix for each of five layers would account for 3,840 bytes of numerical values.

## Where this matters

Real training often retains several intermediates per layer—attention probabilities, normalisation information, feed-forward activations and gradients. Therefore multiplying one saved matrix by the layer count is only a teaching example, not a total training-memory estimate. Framework tape allocation inspection reports what its owner actually retains.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** What is the raw byte size of one FP32 activation table with 20 rows and 24 channels?

<details><summary>Reveal the worked answer</summary>

`20×24×4=1,920` bytes, before metadata, gradients or other operators.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
