# Lesson 191 — Verify the Shifted Token Sequence

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Use the token history to reject an unrelated cache replacement.

## 1. The engineering problem

A full-window replacement must not turn into a back door for loading unrelated context into an existing session. The store checks the exact rolling identity: new positions zero through `C-2` must equal the previous positions one through `C-1`; only the final token may be new. `C` is the context capacity. If a caller wants an unrelated prompt, it should reset the owner and prefill again.

## 2. A worked example

For an old sequence `[10,11,12,13]`, `[11,12,13,14]` is the next legal rolled window. `[10,12,13,14]` is not, even though every individual token ID is valid. Both arrays contain four elements. Shape validation alone would miss the sequencing mistake. The native test confirms the wrong shift returns `INVALID_STATE` without changing keys, values, counters or retained tokens.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** What must the store do with `[11,12,99,14]` after `[10,11,12,13]`?

<details>
<summary>Reveal the worked answer</summary>

Reject it as a shift mismatch. The third new token should be the old fourth token, 13, not 99. A caller may begin a different prompt only through an explicit reset.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/191-verify-the-shifted-token-sequence.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
