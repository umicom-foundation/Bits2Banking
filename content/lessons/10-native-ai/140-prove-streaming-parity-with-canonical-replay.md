# Lesson 140 — Prove streaming parity with an independent replay

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Topic:** Native C23 Transformers, inference and independent validation.

**Learning objective:** Check the complete decoder and sampler, not only a second copy of session state.

## 1. Understand the engineering problem

Two session implementations can agree while sharing the same mistake. Stronger evidence reconstructs a separate canonical reference: build the documented BOS-left-padded context, run the established `UmiAiTrainingStackedDecoderLogits` operation, sample from its last row with the same Framework nucleus sampler, then roll the context. This test is independent of the production session's orchestration. It is kept inside the test suite rather than shipped as a competing inference engine.

## 2. Follow a concrete example

For context `[BOS,BOS,109,114]`, a four-position model returns a `[4,260]` logit table. The reference reads entries 780–1039, because the last row starts at `3 × 260 = 780`. After the reference sampler chooses ID `k`, it rolls to `[BOS,109,114,k]`. Repeating the calculation six times yields a reference sequence. A production session started with the same seed, prompt and policy must return every ID in the same order.

## 3. Implement through the Framework

The new `test_stacked_inference_reference.c` exercises both deterministic top-K=1 and seeded nucleus sampling. It also checks outputs after the context is full and older tokens are evicted. Comparing only the final token would miss an earlier divergence; comparing only row-count estimates would not prove numeric parity. Both checks should accompany checkpoint-identity and failure-atomic output tests.

## 4. Check the boundaries

Do not compare against the separate unpadded-prefix generator: its prompt positions differ. Nor does a successful test prove that a future multi-layer KV cache is equivalent. A cache optimisation requires independent attention-logit comparisons across every layer and position, especially after eviction. The reference deliberately recomputes the whole context.

## Practice

**Question:** Why must the reference read the last real position's logits rather than an arbitrary row?

<details>
<summary>Reveal the worked answer</summary>

The next token is predicted from the final position in the current complete input context. Earlier rows predict from earlier prefixes and can have different causal histories.

</details>

## Continue

[Return to the native stacked inference learning path](stacked-inference-learning-path.md). For the mathematical background, read the [stacked inference mathematics guide](../11-maths-for-ai/stacked-inference-mathematics.md). The canonical APIs are in `framework/include/umicom/ai/training/`; implementations and native tests remain in Umicom Framework, not in this educational repository.

*Service to Many Leads to Greatness.*
