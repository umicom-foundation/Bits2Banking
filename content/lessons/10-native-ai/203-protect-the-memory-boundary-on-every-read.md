# Lesson 203 — Protect the Memory Boundary on Every Read

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Understand output capacities, aliasing and immutable storage.

## 1. The engineering problem

Exposing an internal pointer to a retained K/V row would let a caller accidentally overwrite the model's cache, keep a dangling pointer after reset or race a concurrent operation. The new native owner instead copies exactly one row into two separate caller-owned buffers. It checks layer and token indices, validates both float capacities and refuses overlapping output ranges before writing either array.

## 2. A worked example

With channel width four, each output must have room for at least four `float` values. A three-float destination is rejected even if the other output has ample space. Likewise, if the K result is placed in positions zero through three of an eight-float array and the V result is requested at positions one through four of the same array, they overlap and must be rejected. The caller's original bytes are preserved on both failures.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* outKeys and outValues are disjoint caller-owned float buffers. */
UmiStatus status = UmiAiTrainingStackedKvStoreRead(
    store, layerIndex, tokenIndex,
    outKeys, keyCapacity, outValues, valueCapacity);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why is returning a pointer into the cache less safe than copying one row?

<details>
<summary>Reveal the worked answer</summary>

It would expose mutable internal lifetime and storage layout. A copy provides explicit capacity checks and leaves the store in sole ownership of retained K/V data.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/203-protect-the-memory-boundary-on-every-read.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
