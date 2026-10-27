# Lesson 244 — Treat context rollover as a slow-path gate

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Build an unambiguous routing policy for unchanged-position appends versus full-window rebuilds.

## 1. Understand the problem

The optimisation is intentionally conditional. When a new token can be appended without reassigning prior absolute positions, the session may compute one query and reuse retained K/V. At a full context window under the current learned-position policy, it must select the canonical rebuild path. Mixing a partially shifted cache with freshly computed projections produces a seemingly plausible but numerically different model.

Routing is a correctness rule, not a performance heuristic. The decision should occur before any persistent mutation, and the work counters must distinguish incremental rows, reference fallback work and K/V cache replacement. An eventual alternative policy must pass independent parity tests across the same boundaries.

## 2. Fully worked example

Let capacity be 4 and the current prompt `[A,B]`. Appending `C`, then `D`, keeps earlier position indices fixed. Appending `E` requires a window `[B,C,D,E]` at positions `[0,1,2,3]`; `B` moves from 1 to 0, so the canonical rebuild applies. Another new token forces a second rebuild. A benchmark that stops after generating `D` measures only the easy path.

## 3. Engineering verification and connection to Umicom Framework

Exercise the first rollover, two consecutive rollovers, cancellation just before rollover and checkpoint invalidation immediately after a rebuild. Report the number of fast steps and slow steps beside every latency figure. Do not extrapolate a short-prefix speedup to long, eviction-heavy runs.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 133](../11-maths-for-ai/133-prove-prefix-position-invariance.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why is a test with a prompt shorter than context capacity insufficient?

<details>
<summary>Reveal the worked answer</summary>

It may never trigger eviction. The fast-path contract can pass while the most important position-reassignment boundary remains untested.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](243-keep-single-query-proposals-failure-atomic.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](245-design-adversarial-single-query-fixtures.md)

*Service to Many Leads to Greatness.*
