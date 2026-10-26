# Lesson 202 — Understand Reset and Cancellation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Use explicit lifecycle transitions to keep inference state reproducible.

## 1. The engineering problem

A cancelled generation may leave temporary cache rows that belong to an unfinished prompt. Reusing them for another request would accidentally mix unrelated sequences. The store supports `Reset` to clear retained rows, token IDs and per-prompt counters while preserving the approved model label. Destroying the owner releases its allocation. Neither operation changes the borrowed model because the store does not own one.

## 2. A worked example

A store with four retained tokens and twenty-four computed token-layer rows is reset. Inspection now reports zero retained tokens and zero per-prompt computed rows, but the reserved cache capacity is still available to another prefill of the same model. A new generation against changed weights must instead create a new store with a newly captured model identity. The memory erase is best-effort hygiene and is not a certified secure wipe.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* Explicitly release the old prompt's rows before another prefill. */
UmiStatus status = UmiAiTrainingStackedKvStoreReset(store);
/* The caller must separately verify that the model is unchanged. */
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** After resetting a cache, may the next request begin by appending a token without prefilling?

<details>
<summary>Reveal the worked answer</summary>

No. An append requires a nonempty retained prefix. The new request must explicitly prefill its first token rows and establish its own history.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/202-understand-reset-and-cancellation.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
