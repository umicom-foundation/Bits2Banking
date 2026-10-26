# Lesson 204 — Define the Acceptance Gate for True Incremental Inference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** List the evidence required before replacing canonical full-context evaluation.

## 1. The engineering problem

The K/V owner is now a concrete Framework component, but the complete cached inference engine still needs production-equivalent mathematics. A future implementation must feed the owner from actual layer projections, compute new-token attention using Framework-qualified kernels, handle learned-absolute rollover by rebuilding every layer, verify canonical logits before and after eviction, and prove sampling parity under identical seeds.

## 2. A worked example

An acceptance suite should use at least one-layer and multi-layer models, initial empty-state creation, short prefixes, exact context capacity, first and repeated evictions, invalid weights, checkpoint changes, cancellation, memory budgets and independent held-out examples. Record CPU time and wall-clock time only after parity passes. Separately confirm that full-window fallback behaves identically to the original stacked decoder. Cache work arithmetic alone is insufficient evidence for release.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Which four independent kinds of evidence are necessary for a trustworthy cached inference claim?

<details>
<summary>Reveal the worked answer</summary>

Model/checkpoint identity, numerical logits and token parity, failure-atomic lifetime/memory behaviour, and actual representative performance measurements. Source governance and security checks are additional deployment requirements.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/204-define-the-acceptance-gate-for-true-incremental-inference.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
