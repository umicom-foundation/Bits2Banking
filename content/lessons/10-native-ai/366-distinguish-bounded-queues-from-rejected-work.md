# Lesson 366 — Distinguish bounded queues from rejected work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Choose the correct behaviour when either the queue is full or the K/V pool is temporarily full.

## Technical foundations

The scheduler has a maximum request count, separate from the pool’s maximum concurrent sessions. A request can be accepted into the waiting queue even when all K/V slots are occupied. `Submit` returns `CAPACITY_EXCEEDED` only when the metadata queue has no eligible slot or an explicit counter bound is reached. `AdmitNext` returns `CAPACITY_EXCEEDED` when the pool cannot allocate another K/V lease. These results convey different operational facts; neither should trigger silent loss of already submitted work.

## Worked scenario

If the scheduler holds five requests and the pool supports two active sessions, then at most two requests are ready or dispatched and up to three may wait. A sixth submission fails because metadata capacity is exhausted. Cancelling a waiting request makes a metadata slot available even if the pool is still full. Completing an active request can make K/V capacity available for the oldest waiter.

## Boundary conditions and failure modes

Do not implement an unbounded spin loop repeatedly calling AdmitNext under persistent memory pressure. The user-facing service should apply an explicit wait, timeout or rejection policy outside this primitive. Queue depth is not a measurement of end-to-end request delay without timestamps.

## Practical native Framework exercise

Write a state table for queue capacity five and pool capacity two. Include Submit, AdmitNext, Complete and Cancel. Identify which actions consume bytes and which actions consume only queue metadata.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Which operation owns the physical K/V admission decision?

<details><summary>Show worked answer</summary>

The canonical K/V pool’s Acquire operation. The scheduler only decides the oldest eligible waiting request.

</details>

## Mathematics connection

See [Unit 224](../11-maths-for-ai/224-reconcile-waiting-ready-and-in-flight-state.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](365-apply-backpressure-to-physical-kv-capacity.md)

*Service to Many Leads to Greatness.*
