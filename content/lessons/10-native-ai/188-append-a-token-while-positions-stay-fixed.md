# Lesson 188 — Append a Token While Positions Stay Fixed

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Explain the safe incremental window before the first eviction.

## 1. The engineering problem

While an unpadded prefix grows from position zero, every earlier token keeps its learned absolute index. Causal attention also prevents future tokens from changing a previous token's hidden representation. In that specific interval, an attention implementation can reuse previously calculated projections, provided every layer's original projections were correct. The storage owner supports an `Append` operation only until the fixed context reaches capacity.

## 2. A worked example

Use context capacity four, a two-token prefill and three Transformer layers. Two appends fill the context. The first prefill stores `2 * 3 = 6` token-layer rows; each append adds three, for twelve total. There is no shift yet. A request to append a fifth token must fail rather than silently overwriting position zero, because the first token's eviction would change the remaining tokens' learned positions.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* New K/V projected rows must contain layers * channels floats. */
UmiStatus status = UmiAiTrainingStackedKvStoreAppend(
    store, nextTokenId, layerKeys, elementCount,
    layerValues, elementCount);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** For context four and a two-token prefill, how many successful single-row appends are possible before a rebuild?

<details>
<summary>Reveal the worked answer</summary>

Exactly two. They fill positions two and three. The next token cannot be stored as a fixed-position append because the retained window would need to shift.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/188-append-a-token-while-positions-stay-fixed.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
