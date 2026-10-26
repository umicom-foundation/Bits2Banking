# Lesson 190 — Rebuild the Entire Window After Rollover

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Replace old rows atomically after a context shift.

## 1. The engineering problem

`UmiAiTrainingStackedKvStoreReplaceRolled` accepts a new full set of K/V projection rows for every Transformer layer. It validates the incoming context and every floating-point value before publishing anything. That avoids mixing old-layer and new-layer data in one returned cache. The producer is responsible for calculating the replacement rows through the authorised model implementation; the store only checks shapes, identity labels and safe publication.

## 2. A worked example

For three layers and a four-token context, one replacement stores `3 * 4 = 12` token-layer rows. Starting with twelve from the initial prefill-plus-append sequence, the first rollover brings the cumulative count to 24. The counter records rows admitted to the store, not floating-point operations consumed by the Transformer. One model forward may involve attention-score matrices and activations that this row counter does not measure.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* A complete shifted context and ALL freshly computed layer rows. */
UmiStatus status = UmiAiTrainingStackedKvStoreReplaceRolled(
    store, shiftedIds, contextLength, fullLayerKeys, keyCount,
    fullLayerValues, valueCount);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why cannot the store replace just the last token row when an absolute-position window rolls?

<details>
<summary>Reveal the worked answer</summary>

Earlier tokens have moved to new learned positions; deeper hidden states may also have changed. Every layer and retained row needs fresh projections under the defined full-window reference.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/190-rebuild-the-entire-window-after-rollover.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
