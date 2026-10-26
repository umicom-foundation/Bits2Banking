# Observe real Transformer keys and values

**Bits to Banking · Umicom Foundation**  
**Author and presenter:** Sammy Hegab  
**Format:** Educational narration, on-screen mathematics and C23 reading exercise.

## Learning goals

Explain why a K/V store needs authentic model projections; identify the layer, token and channel axes; and distinguish an observation hook from another attention implementation.

## Opening narration

A Transformer does not remember a sentence as one long string of words. Each layer forms numerical queries, keys and values. The query is used to compare a token with earlier tokens. The key participates in those comparisons, and the value contributes to the attended result. If we intend to retain keys and values, we must know exactly which model and which layer produced them.

Previous lessons introduced a bounded native C23 K/V storage owner. It could accept finite arrays with the correct shapes, but a correct shape does not prove that the numbers came from our Transformer. We now instrument the original native decoder without replacing its numerical code.

## Scene 1 — Follow an unaltered forward pass

**Screen:** Token IDs → token embeddings → positional embeddings → Transformer layers → logits.

**Narration:** The canonical Umicom stacked decoder already owns the complete attention calculation. Its Transformer block exposes a narrow projection callback. Our observation callback performs the **same** Framework tape matrix multiplication as the original block. For key and value roles, it also copies the resulting vectors into temporary storage. Query vectors still flow into the original attention operation. Nothing about the decoder's equations changes.

**Visual annotation:** `K[layer][token][channel]` and `V[layer][token][channel]`. Highlight that each layer has different K/V values because its input state differs.

## Scene 2 — Do the memory arithmetic

Take two layers, four tokens and four channels. One K tensor requires `2×4×4=32` FP32 values; V requires another 32. At four bytes each, raw K and V together occupy `64×4=256` bytes. This excludes the decoder's trained weights, logits, tape nodes and allocation overhead.

Show an explicit offset: layer 1, token 2, channel 3 is `(1×4+2)×4+3=27` in the flattened tensor. Explain that all counts use zero-based indexes in C23.

## Scene 3 — Test transparency

**Screen:** Two columns of logits. Left: original `UmiAiTrainingStackedDecoderLogits`. Right: `UmiAiTrainingStackedDecoderTraceProjections` with its passive observation hook.

**Narration:** Feed both paths the same four token IDs. The test compares all 1,040 logits when vocabulary size is 260. A matching highest-ranked token is not enough. Reject any non-finite value and any difference outside the declared tolerance. This checks hook transparency, not a completely independent attention oracle.

## Scene 4 — Draw the engineering boundary

The trace still performs full-context inference. Copying fewer rows into a store does not erase the computations already performed. We have made the cache's contents more trustworthy, not faster. A genuinely incremental attention implementation must later demonstrate both numerical parity and reduced measured work.

## Learner activity

Calculate K/V storage for three layers, five token positions and eight channels, then explain why the traced logit output must agree with the uninstrumented decoder. Reveal the result: 960 raw FP32 bytes for K and V combined. The logit comparison protects the semantics of the observation hook.

**Continue:** [LLM Lesson 205](../../../lessons/10-native-ai/205-observe-keys-and-values-in-the-real-transformer.md) and [Mathematics Unit 105](../../../lessons/11-maths-for-ai/105-count-projection-tensor-elements.md).
