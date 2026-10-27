# Lesson 368 — Cancel queued and ready sessions safely

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Differentiate pre-admission cancellation, ready-session release and in-flight worker coordination.

## Technical foundations

A waiting request owns no K/V lease, so cancellation only removes queue metadata. A ready request owns a pool lease; cancellation releases it through the existing pool, which either destroys or resets and retains the store according to its configured policy. An in-flight request cannot be cancelled by this cooperative API because the scheduler has no means to stop the caller’s active model operation. The call reports BUSY until that operation has been safely completed or returned uncommitted.

## Worked scenario

Submit A and B; admit A. Cancelling B frees only a scheduler slot. Cancelling A while ready also releases its K/V reservation. If A is dispatched instead, immediate cancellation is refused. The application must stop the computation; only a truly uncommitted unit can be returned and then cancelled without corrupting model state.

## Boundary conditions and failure modes

Cancellation of a request is not secure erasure of every historical memory copy. The pool’s standard C reset and destruction policy provides normal lifecycle hygiene, not a forensic guarantee. Avoid holding borrowed store pointers beyond release or reset.

## Practical native Framework exercise

Write a transition diagram for WAITING → CANCELLED, READY → CANCELLED and DISPATCHED → BUSY. Add the separate application-level action needed before returning an uncommitted work unit.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Why is Cancel forbidden while a quantum is still dispatched?

<details><summary>Show worked answer</summary>

The decoder may be updating session state outside the scheduler. Releasing its lease before that operation stops would risk a use-after-release.

</details>

## Mathematics connection

See [Unit 226](../11-maths-for-ai/226-calculate-layer-major-k-v-store-size.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](367-acknowledge-only-committed-inference-work.md)

*Service to Many Leads to Greatness.*
