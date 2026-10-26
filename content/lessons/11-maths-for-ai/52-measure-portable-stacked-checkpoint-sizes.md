# Measure a portable stacked-model checkpoint

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Gentle mathematics for native AI

## Why file size is more than model weights

A model file needs a header explaining its schema and dimensions, metadata for every tensor, actual weight bytes and an integrity trailer. Umicom's new stacked checkpoint explicitly writes little-endian integers and FP32 value bits instead of writing compiler-dependent C structures directly to disk.

For this educational format, the header is **60 bytes** and the SHA-256 trailer is **32 bytes**. Each parameter tensor stores its row and column counts as two 32-bit integers: `8 bytes` per tensor. A model with two Transformer layers owns `3 + 12×2 = 27` parameter tensors. If it has 1,288 FP32 values (from Unit 47), its encoded size is:

`60 + (27 × 8) + (1,288 × 4) + 32 = 60 + 216 + 5,152 + 32 = 5,460 bytes`.

## Exact layout protects compatibility

The first eight bytes identify the model family. Version, vocabulary, context, channel counts and layer count follow. The next fields contain initial seed, completed steps, tensor count and total value count. After tensor shapes and values, a digest protects the preceding bytes against accidental change.

The digest does *not* authenticate who supplied the file. A copy with modified weights and recomputed digest can still appear self-consistent. Signed provenance is a separate trust gate.

## Practice

One more layer adds 12 parameter tensors and 500 FP32 values in this configuration. How many more checkpoint bytes are required?

<details><summary>Worked answer</summary>

The new shapes require `12×8 = 96` bytes; new FP32 values require `500×4 = 2,000` bytes. Total increase is **2,096 bytes**. The fixed header and digest stay the same length, so the three-layer file would occupy 7,556 bytes.

</details>

---

[Mathematics reading path](stacked-transformer-mathematics.md) · [Native LLM course](../10-native-ai/stacked-transformer-learning-path.md)
