# Lesson 195 — Keep Queries, Keys and Values Distinct

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Avoid mistaking a storage owner for an attention calculation.

## 1. The engineering problem

Self-attention uses three types of projections. A query asks which retained information matters; keys are compared with that query; values are combined using the resulting weights. A K/V cache stores keys and values because previous key/value projections may be reusable under carefully specified semantics. The current store does not save queries or calculate softmax; those operations continue to belong to the Framework's actual attention implementation.

## 2. A worked example

Imagine one head has query `[1,2]`, stored key `[3,4]` and stored value `[5,6]`. The unscaled query–key dot product is `1*3+2*4=11`. The vector `[5,6]` is not another score: it is material used in a weighted sum after softmax. Confusing the two may compile perfectly but implement the wrong model. A cache-storage regression cannot detect that modelling error; an independent logits comparison must detect it.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Why does storing a V row not tell us how strongly that row will influence the next token?

<details>
<summary>Reveal the worked answer</summary>

The influence is computed from the current query and stored keys using scaled dot products and softmax. Values supply content but do not themselves determine attention weights.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/195-keep-queries-keys-and-values-distinct.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
