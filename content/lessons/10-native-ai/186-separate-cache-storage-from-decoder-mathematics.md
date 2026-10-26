# Lesson 186 — Separate Cache Storage From Decoder Mathematics

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Distinguish a validated K/V owner from a functioning accelerated inference engine.

## 1. The engineering problem

A store can copy numerical projection rows and reject invalid states without knowing how a Transformer produced those numbers. That is useful separation of responsibilities. The Framework's canonical stacked decoder remains authoritative for embeddings, normalisation, attention, residual paths and logits. The store accepts a completed K/V row set supplied by a producer and enforces lifetime constraints; it does not calculate attention or claim that those rows agree with a model.

## 2. A worked example

Imagine someone puts `K=[1,2]` into a correctly bounded cache, while the actual decoder would have calculated `[1,3]`. The memory manager may be entirely correct, yet the predictions would be wrong. To demonstrate a real inference optimisation, a future producer must compute K/V from the same frozen weights and compare every vocabulary logit against `UmiAiTrainingStackedDecoderLogits` on the matching context. Today's storage regression is necessary but not sufficient.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Which test would establish a performance improvement: a storage-copy test, or a qualified decoder parity test followed by a benchmark?

<details>
<summary>Reveal the worked answer</summary>

Both correctness and observed timing are required. A copy test proves neither matching logits nor faster generation; a parity test establishes equivalence before timing is interpreted.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/186-separate-cache-storage-from-decoder-mathematics.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
