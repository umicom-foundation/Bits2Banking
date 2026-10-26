# Video lesson — Understand Multi-Layer K/V Storage in Native C23

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Intended audience:** Learners who have completed the introductory Transformer lessons.

## Learning objectives

Explain why every attention layer retains its own keys and values, calculate the raw size of a bounded cache, and distinguish storing a numeric projection from calculating a mathematically correct output token.

## Scene 1 — The question

**Visual:** Three vertically stacked boxes labelled Transformer Layer 0, Layer 1 and Layer 2. Inside each are two separate rows: Key and Value. Four time slots appear along the horizontal axis.

**Narration:** "A Transformer does not have one universal key and value array. The first layer sees token embeddings. The next layer sees representations produced by the first layer, and so on. If we retain a token for future attention, we must know which layer produced each key and each value. This is a storage and lifetime requirement before it becomes a speed optimisation."

**Teaching checkpoint:** Ask the viewer to point to the key for token two in layer one. Explain that layer one and token two are independent indices.

## Scene 2 — Count the storage

**Visual:** A `3 × 4 × 4` matrix shape with each dimension labelled: layers, token positions and channels.

**Narration:** "For three layers, four token positions and four channels, we have three times four times four, or forty-eight floats for K. V needs another forty-eight floats. Ordinary FP32 floats occupy four bytes each. So the raw K and V reservation is ninety-six times four, or three hundred and eighty-four bytes. These are small classroom numbers; real models need more memory for weights, activations, model copies and allocation overhead."

**On-screen calculation:** `2 × 3 × 4 × 4 × 4 = 384 bytes`.

## Scene 3 — One owner, several consumers

**Visual:** An Umicom Framework API box named `UmiAiTrainingStackedKvStore`, with arrows from the authoritative decoder producer and back to future inference consumers. A red crossed-out arrow goes from the public course HTML to the cache implementation.

**Narration:** "Umicom Framework owns the storage contract. The application and educational pages do not implement a second cache. A caller supplies complete, finite K and V rows; the store checks their layout and copies them safely. The store does not compute attention or certify that the decoder produced the right rows. An independent test must still compare the eventual logits against the original decoder."

## Scene 4 — The proof boundary

**Visual:** Two result cards: `Storage checks passed` and `Decoder parity not yet established`. The first is highlighted; the second remains explicitly pending.

**Narration:** "A trustworthy engineering report tells you precisely what was tested. A correct storage owner is necessary for a fast multi-layer cache, but it is not sufficient. We need qualified attention mathematics, independent model-logit comparisons, correct window rollovers and real elapsed-time measurements before promising acceleration."

## Practice and worked answer

**Question:** Four layers, eight tokens and sixteen channels: how many raw FP32 bytes do K and V require?

**Answer:** `2 × 4 × 8 × 16 × 4 = 4,096 bytes`, or 4 KiB. This is not total process RAM.

## Continue

Read [LLM Lesson 185](../../../lessons/10-native-ai/185-own-k-v-rows-for-each-transformer-layer.md) and [Mathematics Unit 91](../../../lessons/11-maths-for-ai/91-calculate-a-three-dimensional-k-v-shape.md). The source of truth for executable behaviour is the native Framework API and its CTest regressions.

*Service to Many Leads to Greatness.*
