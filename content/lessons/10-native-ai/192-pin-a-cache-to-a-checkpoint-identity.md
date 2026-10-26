# Lesson 192 — Pin a Cache to a Checkpoint Identity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Separate content identity from proof of publisher trust.

## 1. The engineering problem

A cache of K/V projections depends on the exact model weights that produced it. Two checkpoints can share tensor shapes yet produce different keys, values and logits. The new store therefore retains an exact 32-byte SHA-256 label supplied by its caller. `CheckIdentity` refuses a different label; but it does not open the checkpoint or establish that the submitted label came from a trustworthy publisher.

## 2. A worked example

A real integration should first call the existing Framework `UmiAiTrainingStackedModelIdentityCapture` and verify the current frozen model before using stored rows. The same model digest must accompany the cache lifetime. A 32-byte digest is commonly displayed as 64 hexadecimal characters. An attacker can recompute an unsigned SHA-256, so content integrity, signed release approval and rights to use training material remain distinct controls.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
/* A matching digest does not certify a publisher. Check the live model
 * separately with the canonical Framework model-identity service. */
UmiStatus status = UmiAiTrainingStackedKvStoreCheckIdentity(
    store, approvedIdentity.checkpointSha256);
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** If two differently trained models both have shape `[4,8]`, can they share one K/V owner?

<details>
<summary>Reveal the worked answer</summary>

Not without a new, independently qualified model state. Matching dimensions do not make their computed K/V rows interchangeable; the exact approved checkpoint identity must match.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/192-pin-a-cache-to-a-checkpoint-identity.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
