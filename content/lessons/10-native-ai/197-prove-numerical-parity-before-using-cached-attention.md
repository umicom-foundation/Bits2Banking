# Lesson 197 — Prove Numerical Parity Before Using Cached Attention

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Set the required independent reference for a future accelerated decoder.

## 1. The engineering problem

The current package validates cache storage, not attention numerics. A future stacked inference backend must produce logits whose values agree with the original `UmiAiTrainingStackedDecoderLogits` under the same learned positions and context policy. Comparing only a selected next-token ID is insufficient: two arrays can choose the same maximum yet encode different probabilities. The reference and candidate must also use the identical frozen checkpoint.

## 2. A worked example

A suitable test records every vocabulary logit at an initial short prefix, immediately before context fills, immediately after first eviction, and after several rollovers. For vocabulary 260 and four comparisons, inspecting only the final row already requires `260*4 = 1040` numeric checks. Additional earlier rows are useful for proving causal-prefix invariance. The acceptance tolerance must be justified in advance for FP32 arithmetic and cannot be widened just to make tests pass.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Does a passing K/V store test authorise switching inference to cached logits?

<details>
<summary>Reveal the worked answer</summary>

No. Only a separate inference implementation that matches canonical logits, sampling, identity and lifecycle behaviour could be admitted for that purpose.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/197-prove-numerical-parity-before-using-cached-attention.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
