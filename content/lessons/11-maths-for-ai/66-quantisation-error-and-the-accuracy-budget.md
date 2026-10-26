# Unit 66 — Understand quantisation as a controlled numerical approximation

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

Suppose a floating-point value is `0.73` and a simple uniform quantiser stores the closest multiple of `0.1`. Its reconstruction becomes `0.7`, producing an absolute difference of `|0.73−0.7|=0.03`. Smaller storage is not a free numerical improvement.

## Where this matters

A real model has many weights and operations. The error in output logits is not generally the same as the error in each individual weight. Test the complete model and representative data, then compare held-out loss, accuracy and numerical behaviour. Quantisation must have its own checkpoint format and validated scale information.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** What absolute error results when 0.26 is rounded to the nearest 0.05?

<details><summary>Reveal the worked answer</summary>

0.26 rounds to 0.25, so the error is `0.01`.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
