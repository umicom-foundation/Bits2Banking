# Lesson 193 — Reject Non-Finite Projection Values

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Protect numerical state before a bad float enters attention.

## 1. The engineering problem

A floating-point tensor can contain ordinary finite values, positive or negative infinity, or NaN (not a number). A NaN in one key may propagate through attention scores and contaminate an entire output distribution. The store checks every element in the supplied K and V arrays with the native finite-value predicate before copying. If any one element is invalid, the whole operation is rejected.

## 2. A worked example

Consider a full replacement of 48 floats for keys and 48 for values. The first 47 K values might be valid, while key element 47 is NaN. Accepting 47 entries and failing at the last would create a cache where some layers no longer match others. Instead, the store rejects the entire 96-float proposal and retains the previous complete state. A native regression reads a row before and after rejection and verifies byte-for-byte equality.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why does a finite-value scan belong before the first stored copy?

<details>
<summary>Reveal the worked answer</summary>

It prevents an invalid last element from creating a mixed old/new cache. Failure atomicity is about complete state transitions, not just reporting an error code.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/193-reject-non-finite-projection-values.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
