# Count parameters in several Transformer layers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## Start with familiar multiplication

A parameter is one trainable number. A matrix with eight rows and eight columns stores `8 × 8 = 64` parameters. Our current pre-layer-normalised Umicom block has *four* eight-by-eight attention projections: query, key, value and attention output. Together they contain `4 × 64 = 256` weights.

A feed-forward block expands eight channels to twelve and contracts twelve back to eight. Its two weight matrices contain `8 × 12 = 96` and `12 × 8 = 96` values, or 192 altogether. The two layer-normalisation scales/biases contribute `4 × 8 = 32` values. Feed-forward biases contribute `12 + 8 = 20`. **One Transformer block therefore has `256 + 192 + 32 + 20 = 500` parameters.**

## Count the whole model

Add two such blocks: `2 × 500 = 1,000`. For vocabulary size 16 and channels eight, token embeddings contribute `16 × 8 = 128`. Four positions contribute `4 × 8 = 32`. The final vocabulary projection contributes `8 × 16 = 128`. So the complete parameter count is `1,000 + 128 + 32 + 128 = 1,288`.

FP32 values occupy four bytes each: raw parameter values need `1,288 × 4 = 5,152 bytes`. This is not total training memory: gradients, graph nodes, optimizer state and scratch storage need more.

## Practice

Keep every dimension the same but use three Transformer blocks. How many parameters are there?

<details><summary>Worked answer</summary>

The non-block parameters total `128 + 32 + 128 = 288`. Three blocks contribute `3 × 500 = 1,500`. Total `1,788` parameters, or 7,152 raw FP32 bytes.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
