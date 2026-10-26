# Understand greedy generation and context rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Training logits are not yet a chat service

The stacked decoder returns a complete matrix of vocabulary logits for one fixed input context. A simple inference demonstration can select the largest score from the last row, breaking ties towards the lowest token ID. `UmiAiTrainingStackedDecoderPredictNext` exposes this raw ID prediction. `UmiAiTrainingStackedDecoderGenerateGreedy` repeats it, shifting the context left between requested tokens.

The current laboratory does **not** supply temperature sampling, a streaming chat protocol, tool-use permissions, an EOS stopping policy or verified natural-language capability. Greedy token IDs may include reserved special IDs. Never execute generated text as source code or financial instructions.

## Where work grows

With context length `C` and generated length `G`, this implementation performs `G` complete forward passes. Each pass runs every Transformer layer. Unlike the earlier single-block KV-cache study, there is no qualified per-layer cache for the stacked model. The reference workload processes `C × G` token rows **per layer**, plus token embedding and final projection work.

For example, three layers, context eight and five generated tokens give `3 × 8 × 5 = 120` layer-token evaluations. This is a simple work counter, not elapsed time or a claim about multiply-add count. The implementation does not claim a multi-layer KV-cache speedup.

## Why a cache needs more proof

When the oldest token leaves the window, learned absolute position indices shift. The hidden representation in an upper Transformer layer may also depend on earlier context, even if RoPE were later used. Preserving cached keys/values without proving the new context semantics risks changing model outputs.

## Practice

What is the layer-token forward-work count for four layers, context length 12 and seven generated tokens?

<details><summary>Worked answer</summary>

`4 × 12 × 7 = 336` layer-token evaluations. It is not an actual runtime measurement. Benchmark with the same model, prompt, toolchain, warm-up and sampling semantics before discussing performance.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
