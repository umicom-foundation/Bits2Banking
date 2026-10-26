# Estimate full-context generation work across layers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## Work grows with layers and generated tokens

An autoregressive decoder samples or selects a token, adds it to the context and repeats. Without a qualified KV cache, the implementation can re-evaluate a full context for every generated token. The simplest workload counter is the number of token positions processed by Transformer blocks: `layers × contextLength × generatedTokens`.

With three layers, eight context positions and five generated tokens: `3 × 8 × 5 = 120` layer-token evaluations. The model also performs token/position embedding lookups, a vocabulary projection and attention calculations within each block. Therefore 120 is not a FLOP count and not elapsed CPU time.

## Attention itself depends on context width

During each full evaluation, each token may attend to earlier positions. With a causal mask, the number of allowed query/key pairs for one sequence of length C is `1 + 2 + ... + C = C(C+1)/2`. With C=8 this is `8×9/2 = 36` pairs per attention head per layer. A full eight-by-eight score matrix has 64 entries, some of which would be masked; practical kernels vary in whether they physically calculate all entries.

## What a cache cannot assume

The current stacked decoder uses learned absolute positions. Moving tokens after window eviction changes their position embeddings. Upper-layer state may depend on history that has been discarded. RoPE alone is not sufficient to claim identical upper-layer outputs after window truncation. Prove numerical semantics before promising reuse.

## Practice

For four layers, three heads, context 12 and seven generated tokens, calculate layer-token evaluations and permitted causal query/key pairs per layer/head for one full-context pass.

<details><summary>Worked answer</summary>

Layer-token evaluations: `4×12×7 = 336`. Permitted causal pairs per head per layer per full evaluation: `12×13/2 = 78`. They measure different work units; neither is directly a wall-clock measurement.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
