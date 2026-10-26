# Lesson 216 — Design the next incremental-attention acceptance reference

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** C23  
**Scope:** Educational native model engineering; not production deployment.

**Learning objective:** Define a measurable, falsifiable contract before replacing full-context execution with true incremental attention.

## Why this matters

The observation milestone proves that Framework can capture the decoder's **real** keys and values, verify causal prefix stability and rebuild all positions after rollover. It does not change attention execution. A true incremental implementation needs a new qualified computational path that consumes these projections to produce the same final logits without reevaluating the entire fixed-position prefix.

The acceptance test must compare every vocabulary logit under identical checkpoint identity, prompt positions, sampling policy and output step. It must include short prefixes, the last available prefix slot, the first eviction, repeated evictions, incorrect tokens, training invalidation and memory-budget errors. Model inference and sampling must be tested separately to avoid errors cancelling one another.

A benchmark is the final phase, not the first. Only after numerical parity can a timed test report median wall-clock latency, measured memory and the actual number of executed token-layer operations under warmed and repeated runs. If no speedup is measured, report that result rather than promoting a prediction.

## Work through the numbers and tensor shapes

Example acceptance matrix for an eight-token context: examine prefix lengths one, four, seven and eight. For each, compare canonical and candidate logits over every vocabulary entry. Then append the ninth token to a full window and verify the shifted-position rule. Repeat with at least two distinct model seeds and trained checkpoint states.

Keep tolerance fixed in advance, such as an appropriately justified absolute plus relative bound, and reject non-finite outputs. Counts of stored K/V rows belong in a separate column from actually executed decoder work.

## Where the implementation lives

The reusable implementation belongs to `Umicom-Applications/framework`. Use the public `umicom/ai/training/stacked_projection_trace.h` or `umicom/ai/training/stacked_kv_capture.h` interfaces, depending on the task. The trace observes the **original** decoder through its established Transformer projection hook; the existing cache store handles K/V row ownership. No C23 neural-network computations belong in the Bits2Banking course. Run the Framework CTest cases for numerical qualification on the actual model before interpreting these services as integrated.

## Limitations and engineering evidence

The current observation pipeline performs a **complete canonical Transformer forward** for each observed prompt state. A smaller number of rows accepted into a store is not proof of fewer operations, lower latency or more accurate generated text. SHA-256 identifies checkpoint bytes but does not authenticate a publisher. No generated output should be executed as source code or treated as financial advice.

## Practice

**Question:** What result would justify saying “incremental inference is faster” rather than “the cache stores fewer rows”?

<details><summary>Reveal the worked explanation</summary>

A truly incremental implementation must match the declared canonical mathematical reference and show repeatable measured latency or throughput improvement for a specified workload, build and machine. A storage counter alone is insufficient.

</details>

## Continue studying

[Previous lesson](215-interpret-causal-stability-and-evicted-history.md) · [View the browser lesson](../../courses/llm-from-scratch/lessons/216-design-the-next-incremental-attention-reference.html) · [K/V projection learning path](kv-projection-observation-study-route.md).

*Service to Many Leads to Greatness.*
