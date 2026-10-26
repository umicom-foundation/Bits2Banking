# Lesson 199 — Plan a Fair K/V Performance Experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Native C23, Transformer inference and reliable cache ownership.

**Learning objective:** Separate correctness, token-layer work, allocation and measured latency.

## 1. The engineering problem

A cache can store fewer projection rows yet run slower than a full-context implementation. More memory copies, allocation churn or poorly batched matrix kernels may outweigh arithmetic savings. A fair experiment starts only after numerical parity and checkpoint identity are established. Run both paths against the same model, prompt, seed, sampling policy, device, compiler flags and requested output count. Repeat trials and alternate their execution order.

## 2. A worked example

Suppose a future qualified candidate computes 60 token-layer rows instead of 84, but median wall-clock time is 7.2 ms rather than 6.0 ms. The row-work reduction is `(84-60)/84 ≈ 28.6%`, yet the candidate is `7.2/6.0 = 1.20` times the elapsed duration. It is twenty per cent slower in that example. Neither fabricated duration belongs in a production report; these figures illustrate interpretation only.

## 3. Put this into the existing Umicom Framework

The Framework defines the relevant interface in `include/umicom/ai/training/stacked_kv_store.h` and implements it in `src/ai/training/stacked_kv_store.c`. Work-count qualification composes the existing `stacked_prefix_cache_plan.h` contract; the data owner must never be copied into Umicom Studio or Bits2Banking. Calls must be externally serialised, with inputs retained long enough for validation and one successful copy.

**Implementation check:** Inspect the actual K/V owner and its four focused regression cases. Identify the validation that prevents the problem above, then compare the returned `UmiStatus` against the expected outcome. Do not infer mathematical model parity from storage tests.

## 4. How to verify the result

**Engineering boundary:** This chapter's C23 cache component stores and validates rows supplied by an approved producer; it does not calculate canonical stacked decoder logits, supply a new attention kernel, authorise training material or establish an end-to-end inference speedup. Reuse the established Umicom Framework decoder, checkpoint identity and attention services for those responsibilities.

The optional native laboratory lives under `framework/learning/native-ai-stacked-kv`. Its tests compile the real K/V storage and the established scaling and prefix-work estimators. An actual accelerated decoder must separately pass independent logit parity, rollover and sampled-token regressions. Measure elapsed inference time only after those gates succeed.

## 5. Practice and worked answer

**Exercise:** If row count decreases but wall-clock time increases, which conclusion is justified?

<details>
<summary>Reveal the worked answer</summary>

The specified workload requested fewer rows, but the observed implementation was slower. Do not announce a speedup or infer that row counts determine timing.

</details>

## Continue learning

[Open the HTML version of this lesson](../../courses/llm-from-scratch/lessons/199-plan-a-fair-k-v-performance-experiment.html). Read [the multi-layer K/V learning path](multi-layer-kv-storage-learning-path.md) or revisit [conditional prefix work](194-measure-stored-token-layer-work.md).

*Service to Many Leads to Greatness.*
