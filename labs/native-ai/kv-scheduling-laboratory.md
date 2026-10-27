# Native AI laboratory — Bounded multi-session K/V scheduling

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation:** C23 via Umicom Framework; no application-specific scheduling scripts.

## Learning outcome

Distinguish queue admission, per-request scheduling, persistent cache ownership, and neural generation. Reuse the existing Framework pool, memory planner and stacked decoder instead of implementing another KV cache in an application.

## Architecture

```text
Application request queue (bounded metadata)
       | Submit / AdmitNext
       v
Framework stacked KV scheduler ──> Framework KV pool
       | Dispatch ticket                | one checkpoint-bound store per active lease
       v                                v
Application-owned decoder session ---> Framework native attention and inference APIs
       | successful committed step
       v
Scheduler Acknowledge -> optional release / canonical KV reset
```

This is a cooperative control-plane service: **no** CUDA kernel, background thread, general-purpose GPU batcher, model authentication or measured inference speedup is supplied by the scheduler.

## Exercise A — Use the native Framework APIs

Create a `UmiAiTrainingStackedKvPool` using a bounded config, then borrow it when creating `UmiAiTrainingStackedKvScheduler`. The pool must outlive the scheduler. Submit three requests with step budgets 2, 2 and 1. Use `AdmitNext` to acquire the first two actual leases. Expect the third admission to be rejected while the pool is full, with its waiting request intact.

Call `Dispatch`, then perform one independently validated application work step. Acknowledge only after success. Use `ReturnUncommitted` only when the application guarantees no decoder or K/V state was committed. Continue until capacity becomes available for the third request.

## Exercise B — Memory and fairness

For two Transformer layers, four context positions and eight channels, FP32 key/value storage is `2 * 2 * 4 * 8 * 4 = 512 bytes` per store. A 1,024-byte raw budget admits two stores. Inspect `UmiAiTrainingStackedKvPoolStats` and scheduler counters before and after each step. Verify the sequence A,B,A,B,C under the declared admission timing.

## Exercise C — Negative testing

Test queue-full rejection, full-pool admission rejection, duplicate request ID, stale scheduler ticket, foreign scheduler identity, cross-pool KV lease, in-flight cancellation, a returned uncommitted work unit and an old pool lease after idle reuse. Verify invalid calls do not change caller-owned output buffers or live state.

## Test infrastructure

The Framework CMake module is `cmake/UmicomAiStackedKvScheduler.cmake`, with registered test names `framework.ai.stacked_kv_scheduler.fairness`, `.admission`, `.cancellation` and `.boundaries`. The example project at `learning/native-ai-kv-scheduler` includes that module for standalone lab builds within an existing Framework checkout.

A controlled test double may isolate the scheduling API in a separate laboratory. Evidence from that test is not equivalent to qualification against the installed Framework SDK's real K/V storage or to full vocabulary-logit parity against the canonical decoder.

## Questions

1. Why does successful submission not allocate a K/V store?
2. Why must a completed final step release its pool lease before invalidating its ticket?
3. Why do dispatch counters not represent measured output tokens per second?
4. Under what conditions is retrying a returned uncommitted unit safe?

## Worked answers

1. The metadata queue is separate from pool-backed active resources. Admission is explicit.
2. Release can fail, and premature ticket invalidation could orphan a live allocation.
3. A dispatch grants one caller-defined quantum with no timestamp or neural result.
4. Only when the caller has independently established that no earlier attempt committed model, cache or published output changes.

## Further reading

- [Orca — iteration-level serving scheduling](https://www.usenix.org/conference/osdi22/presentation/yu)
- [PagedAttention and vLLM — KV memory handling](https://arxiv.org/abs/2309.06180)

*Service to Many Leads to Greatness.*
