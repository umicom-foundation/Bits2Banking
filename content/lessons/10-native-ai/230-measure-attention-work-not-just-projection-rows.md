# Lesson 230 — Measure attention work, not just projection rows

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Level:** Building beyond the introductory Transformer.

**Learning objective:** Separate projected token-layer counts, attention query-row execution, allocation and wall-clock time.

## 1. The engineering question

An incremental composition can avoid recalculating old Q/K/V while still calling an attention operator that processes all query rows. Claiming speed from projection counts alone would hide this real work. Current Framework reports observed canonical trace rows, incrementally projected rows and query-layer work separately.

## 2. Work through a concrete example

For context 6, two layers, prompt 2 and seven samples: the reference asks for 7×6×2=84 token-layer rows. The opt-in path performs 36 full-context token-layer rows and 8 newly projected rows, but its causal-attention operations evaluate 72 query-layer rows in total. These are different counters, not interchangeable FLOP totals.

## 3. How Umicom Framework implements the idea

`UmiAiTrainingStackedKvIncrementalSessionInspect` exposes counters without inventing elapsed time. A performance study must repeat equivalent test cases in Debug and Release, distinguish CPU time from wall time and report complete timing distributions.

The relevant public contract is `umicom/ai/training/stacked_kv_incremental.h`. The native implementation and numerical tests belong to Umicom Framework; this manuscript does not introduce an alternative application-local training or inference service. The training tape owns mathematical operators and tensor lifetimes, while consumers use explicit C23 handles and status results.

## 4. Check the mathematical foundation

For a step-by-step explanation of the arithmetic, read [Mathematics Unit 121](../11-maths-for-ai/121-separate-projection-work-from-attention-work.md). Keep tensor **shape**, **absolute position**, **model checkpoint identity** and **actual executed work** distinct when describing a cache.

## 5. Practice and verify

**Question:** Can 44 total projected token-layer rows versus 84 reference rows establish a 47.6% wall-clock speedup?

<details>
<summary>Reveal the worked explanation</summary>

No. It counts only particular projection-row work; attention still executes many rows, and allocations, scheduling, cache access and other operations contribute to runtime.

</details>

## 6. Limits and responsible interpretation

The reported query-layer count is not a clock measurement, and further kernel fusion requires independent numerical evidence.

A passing test in an isolated demonstration is not a production integration result. Evaluate against the actual Framework checkout and document any numerical or timing limitations before making deployment claims.

## Continue learning

[Previous lesson](229-handle-full-window-rollover-correctly.md) · [Next lesson](231-preserve-inference-state-on-errors.md) · [Browser learning path](../../courses/llm-from-scratch/incremental-attention-learning-path.html)

*Service to Many Leads to Greatness.*
