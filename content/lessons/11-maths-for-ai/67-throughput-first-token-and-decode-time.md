# Unit 67 — Calculate tokens per second without hiding prefill

**Mathematics for AI · Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Start with ordinary numbers

A generation request produces 100 tokens in 4 seconds. The complete-request throughput is `100/4 = 25 tokens/s`. If one second was spent preparing the prompt, the remaining decode time is three seconds and the decode-only throughput is `100/3 ≈ 33.33 tokens/s`.

## Where this matters

Both numbers may be useful but must be labelled accurately. Time to first token, median inter-token latency, total wall-clock latency and peak memory answer distinct engineering questions. Changing the denominator without telling the reader misrepresents performance.

The arithmetic above is independent of the computer language. Native Umicom Framework components perform the actual tensor computation, memory checks and training/inference operations. Use the numbers to verify your own reasoning before running a test.

## Practice with a worked answer

**Question:** A model produces 60 tokens in 3 seconds, including 0.5 seconds of prefill. Compute both rates.

<details><summary>Reveal the worked answer</summary>

Complete-request throughput is `60/3=20 tokens/s`; decode-only throughput is `60/2.5=24 tokens/s`.

</details>

## Continue learning

Start from [attention and KV-cache arithmetic](08-attention-and-kv-work.md) or [the stacked inference mathematics reading route](stacked-inference-mathematics.md), then continue with [the native LLM course](../10-native-ai/148-build-and-qualify-native-stacked-inference.md).

*Examples are synthetic and do not represent production financial calculations.*
