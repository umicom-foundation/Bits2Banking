# Lesson 185 — Own K/V Rows for Each Transformer Layer

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Follow the lifetime of key and value projections without writing a second attention implementation.

## 1. The engineering problem

A multi-layer Transformer has a separate K and V tensor at every layer. The same token index in layer zero and layer two represents different learned transformations. A native cache therefore cannot be a single anonymous vector array: it needs a layer dimension, a time position, a channel count, and an owning lifetime. The new `UmiAiTrainingStackedKvStore` keeps all of those dimensions together and copies rows into its own allocation. Callers do not receive a pointer to private storage.

## 2. A worked example

For three layers, four context tokens and four projected channels per token, K requires `3 * 4 * 4 = 48` floats. V requires another 48. At four bytes per float, the raw K/V reservation is `96 * 4 = 384` bytes. This does not include model weights, activations, heap bookkeeping or the training tape. Two arrays with equal byte counts can still represent different tensor roles; they must not be exchanged.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
#include "umicom/ai/training/stacked_kv_store.h"
/* config.checkpointSha256 is an approved *existing* model digest. */
UmiAiTrainingStackedKvStore *store = NULL;
UmiStatus status = UmiAiTrainingStackedKvStoreCreate(&config, &store);
/* Caller must supply actual precomputed K/V rows, not invented data. */
if (status == UMI_STATUS_OK) UmiAiTrainingStackedKvStoreDestroy(store);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Explain why a single K array without a layer index is insufficient.

<details>
<summary>Reveal the worked answer</summary>

Different layers calculate keys from different hidden states and projections. A layer index is necessary to retrieve the matching state, and it does not authorise reusing a row after a context shift.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/185-own-k-v-rows-for-each-transformer-layer.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
