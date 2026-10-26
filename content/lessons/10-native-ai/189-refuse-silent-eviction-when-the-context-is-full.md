# Lesson 189 — Refuse Silent Eviction When the Context Is Full

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Understand why capacity is a correctness rule, not merely a memory limit.

## 1. The engineering problem

An ordinary ring buffer may overwrite its oldest element when it fills. That behaviour is unsafe for the present learned-absolute stacked decoder. When token B moves from absolute position one to zero, its input position embedding changes; the hidden states of subsequent blocks can also depend on earlier history. The store deliberately has no overflow-append behaviour. It requires an explicit full-window replacement instead.

## 2. A worked example

With context `[A,B,C,D]`, a fifth token E produces `[B,C,D,E]`. The new window has the same length, but its contents are mathematically new inputs at positions zero through three. Reusing saved K/V rows for B, C or D would not prove canonical equivalence. The cache API's rejected append preserves all four original rows and its counters; an independent caller must calculate the full replacement before asking the store to publish it.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** Does a four-slot ring of correct floating-point arrays automatically make a correct rolling Transformer cache?

<details>
<summary>Reveal the worked answer</summary>

No. Correct memory storage cannot make a stale projection numerically valid after positional rebasing. The full shifted context must be re-evaluated under the current architecture.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/189-refuse-silent-eviction-when-the-context-is-full.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
