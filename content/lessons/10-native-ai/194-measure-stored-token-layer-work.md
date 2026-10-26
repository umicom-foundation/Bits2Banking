# Lesson 194 — Measure Stored Token-Layer Work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Reconcile actual store counters with the conditional Framework work planner.

## 1. The engineering problem

The previously introduced `UmiAiTrainingStackedPrefixCachePlanBuild` estimates how many token-layer rows a hypothetical cache would calculate for a declared prompt and generation length. Now a real K/V owner can report how many rows its producer supplied and stored. The new `UmiAiTrainingStackedKvWorkQualify` compares those numbers, along with prefill size, single-row appends and full-window rebuilds. It rejects mismatches rather than publishing attractive but inconsistent savings.

## 2. A worked example

For context C=4, layers L=3, prompt P=2 and generated samples G=7, the final sample is pending. There are G-1=6 context transitions: two single-row appends and four full rebuilds. The cache work is `L * (P + 2 + 4*C) = 3*(2+2+16) = 60` token-layer rows. The full-reference forecast is `L*C*G = 3*4*7 = 84`; the conditional difference is 24. Neither count directly measures milliseconds.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

The following excerpt assumes the caller has already prepared valid tensors and all variables named in it. It illustrates the public boundary; it is not a standalone program.

```c
UmiAiTrainingStackedKvWorkAudit report = {0};
UmiStatus status = UmiAiTrainingStackedKvWorkQualify(
    store, &approvedPlan, &report);
/* On success, the observed storage counters match the original planner.
 * This is NOT numerical decoder parity or a timing measurement. */
```

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** What if the owner reports 57 rows where the planner predicts 60?

<details>
<summary>Reveal the worked answer</summary>

The work qualification must fail. It should not publish a claimed reduction or silently adjust the forecast to the observed value.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/194-measure-stored-token-layer-work.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
