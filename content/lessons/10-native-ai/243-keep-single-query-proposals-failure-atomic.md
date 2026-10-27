# Lesson 243 — Keep single-query proposals failure-atomic

**Bits to Banking · Umicom Foundation**  
**Course lead:** Sammy Hegab  
**Language:** Native C23 and Assembly where justified · **Level:** Advanced native Transformer engineering.

**Learning objective:** Design rejection and cancellation boundaries that never leave half-published inference state.

## 1. Understand the problem

A candidate kernel can finish successfully even when sampling, an output callback or cache publication later fails. The session must therefore distinguish **calculation**, **proposal**, **validation** and **commit**. Calculating a query output should not mutate persistent K/V rows, generated-token counters, exposed output buffers or random-number-generator state.

If a generated token has already been sampled, a failed commit must not silently consume the random draw. Either restore the generator state or make a documented monotonic, replayable transaction boundary. The exact behaviour must follow the existing Framework session contract, rather than being invented independently by the course.

## 2. Fully worked example

State before step: prefix `[A,B]`, valid length `2`, token count `0`, deterministic sampler state `S`. During proposal a third token `C` and its projections are computed, but an output buffer is too small. After rejection, the state must still be `[A,B]`, length `2`, count `0`, sampler state `S`, and the cache version unchanged. Retrying with an adequate buffer should yield the same candidate token.

## 3. Engineering verification and connection to Umicom Framework

Inject failures at scratch allocation, projection calculation, nonfinite detection, output-capacity validation, callback acceptance and K/V commit. For each, compare pre- and post-state snapshots. Test cancellation just before and just after the designated publication boundary so that callbacks cannot observe a partially committed token.

The existing Umicom Framework decoder, training tape and K/V ownership services remain the authority for implementation. This educational lesson specifies behaviour; it does **not** introduce a competing application-local inference engine or claim that the proposed single-query kernel is already merged or performance-qualified.

## 4. Mathematics connection

Review [Mathematics for AI — Unit 132](../11-maths-for-ai/132-calculate-cache-and-scratch-memory.md). The mathematics companion includes a calculation that can be verified independently of a compiled model.

## 5. Exercise

**Question:** Why should random-state rollback be included in a cache-publication test?

<details>
<summary>Reveal the worked answer</summary>

Without it, a failed attempt can alter subsequent sampled tokens even when the cache rows and token history appear unchanged.

</details>

## 6. Acceptance note

Educational calculations and design specifications are not substitutes for running the complete numerical and memory-safety qualification suite against the actual Windows and other supported Framework builds. Do not claim an inference speedup from hypothetical arithmetic counts.

## Continue learning

[Previous lesson](242-validate-cache-identity-shape-and-lifetime.md) · [Browser learning path](../../courses/llm-from-scratch/single-query-attention-learning-path.html) · [Next lesson](244-treat-context-rollover-as-a-slow-path-gate.md)

*Service to Many Leads to Greatness.*
