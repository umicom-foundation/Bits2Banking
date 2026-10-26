# Lesson 196 — Read the Layer-Major K/V Layout

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Translate a three-dimensional tensor address into a safe C array index.

## 1. The engineering problem

The store's persistent layout is `[layer][context slot][channel]` for keys followed by an equal-size region for values. This fixed-stride arrangement lets a caller read any retained row by giving a layer and token index. The public `Read` API copies values into caller-owned float arrays; it does not expose pointers to the internal allocation or let an application modify a cached row in place.

## 2. A worked example

For three layers, context four and channel width four, the first element of layer two, token three has zero-based offset `(2*4+3)*4 = 44` floats into the K region. Because the V region begins after `3*4*4 = 48` floats, the analogous V entry has overall offset 92. An initial two-token prefill is supplied in compact `[layer][2][channel]` order; the store expands its rows into fixed-context strides.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* Copy exactly one row from the specified layer and token slot. */
float key[16] = {0};
float value[16] = {0};
UmiStatus status = UmiAiTrainingStackedKvStoreRead(
    store, layerIndex, tokenIndex, key, 16U, value, 16U);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why is compact prefill input indexing different from a fixed-capacity stored cache offset?

<details>
<summary>Reveal the worked answer</summary>

The compact input stride is the number of supplied tokens, while the stored layout reserves the whole context length for each layer. The public API handles the conversion.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/196-read-the-layer-major-k-v-layout.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
