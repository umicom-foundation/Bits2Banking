# Lesson 212 — Distinguish accepted K/V rows from actual decoder work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Read the two independent sets of counters without turning logical storage savings into false speed claims.

## Why this matters

Metrics can mislead when their units are not clear. A key/value store may admit one new row per layer after validating a growing prefix. If the producer recomputed the entire Transformer to obtain that row, the application still incurred full-context computation. The new capture service reports these quantities **separately**.

`acceptedTokenLayerRows` comes from the real storage owner. `actuallyEvaluatedTokenLayerRows` counts complete reference evaluations multiplied by context length and number of layers. The latter is the truthful description of what this diagnostic pipeline does today. Neither quantity measures FLOPs, wall-clock duration, energy or GPU transfer cost.

A future incremental attention implementation may reduce actual computations; its success criterion will be fewer observed operations **and** independent logit parity for every tested prefix and rollover. Until then, use neutral terms such as 'stored rows' and 'reference rows', not 'accelerated inference'.

## Work through the numbers and tensor shapes

For `C=8`, `P=3`, `L=2`, `G=12` requested generated tokens in a hypothetical future streaming design, the existing planner gives `12 × 8 × 2 = 192` reference token-layer rows and a conditional cached-row forecast of 112. That estimate assumes real one-row work while positions remain stable.

A diagnostic capture which performs twelve full references still evaluates 192 token-layer rows. It can *store* only 112 cumulative rows, but it has **not** saved 80 executed token-layer rows. Compare the benchmark's measured wall time only after both paths are genuinely implemented and qualified.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** How can a report truthfully show fewer stored K/V rows than reference-computed rows without demonstrating a faster decoder?

<details><summary>Reveal the worked explanation</summary>

Storage acceptance and numerical execution are different events. A full reference can calculate many rows and preserve only a subset. The computation has already occurred, so no speedup follows from storing fewer rows.

</details>

## Continue studying

[Previous lesson](211-rebuild-all-layers-after-absolute-position-rollover.md) · [Next lesson](213-test-capture-error-atomicity-and-memory.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/212-distinguish-stored-rows-from-computed-rows.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
