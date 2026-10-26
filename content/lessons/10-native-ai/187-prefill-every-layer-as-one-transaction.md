# Lesson 187 — Prefill Every Layer as One Transaction

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Build a complete initial cache while preserving outputs after invalid inputs.

## 1. The engineering problem

Prefill means the first calculation that establishes state for an initial prompt. The store accepts token IDs and an exact pair of float arrays in `[layer][token][channel]` order. Every token ID must be within the declared vocabulary; every K/V entry must be finite; and the number of elements must match the model shape. The store validates all inputs before copying its first row, so a later invalid value cannot leave a partly usable cache.

## 2. A worked example

Suppose there are two layers, three prompt tokens and four channels. Each array contains `2 * 3 * 4 = 24` floats. If an adapter passes only 23 floats, it must receive a capacity/argument rejection before either internal K or V changes. The next call can correct the count and prefill successfully. After that, the same prefill call is refused until the owner is explicitly reset. A partial overwrite would make the cached prefix ambiguous.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* Two layers, three prompt tokens and four channels: 24 floats per K/V. */
UmiStatus status = UmiAiTrainingStackedKvStorePrefill(
    store, promptIds, 3U, keyRows, 24U, valueRows, 24U);
/* The store does not compute keyRows or valueRows. */
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why must the final float be checked before writing the first internal row?

<details>
<summary>Reveal the worked answer</summary>

A failure-atomic prefill publishes only complete state. Checking the whole input first prevents a late invalid element from leaving earlier rows written and a misleading partially initialised prefix.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/187-prefill-every-layer-as-one-transaction.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
