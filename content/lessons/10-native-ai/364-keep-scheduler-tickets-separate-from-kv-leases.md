# Lesson 364 — Keep scheduler tickets separate from KV leases

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Recognise two distinct ownership domains and avoid treating their identity fields as interchangeable.

## Technical foundations

The scheduling ticket contains `schedulerIdentity`, `generation` and `slotIndex`. It identifies a live queue entry; it neither holds K/V tensors nor proves checkpoint authenticity. After admission, a separate `UmiAiTrainingStackedKvLease` identifies one store in the borrowed K/V pool with its own `poolIdentity`, generation and slot. A successful dispatch returns both. Each API validates the identity appropriate to its layer. The application continues to verify the live decoder checkpoint before using retained projections.

## Worked scenario

A job in scheduler slot 1 might be mapped to K/V pool slot 0, because those two managers allocate independently. The numbers do not have to match. After completion the scheduler slot can be reused with a larger scheduler generation. After pool release, an old lease is independently invalidated by the pool generation.

## Boundary conditions and failure modes

Never compose a lease by copying a scheduler slot index or assume that matching numerical generations imply matching owners. A SHA-256 checkpoint label detects changed bytes but is not a digital signature of provenance.

## Practical native Framework exercise

In a diagram, draw an old ticket, a new ticket with the same slot but different generation, an old K/V lease and a new lease. Label which validation checks reject each stale object.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Can a scheduler ticket be passed into StackedKvPoolRead?

<details><summary>Show worked answer</summary>

No. PoolRead requires an authentic K/V pool lease. The scheduler ticket only identifies a scheduling request.

</details>

## Mathematics connection

See [Unit 223](../11-maths-for-ai/223-derive-round-robin-dispatch-sequences.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](363-dispatch-one-work-quantum-with-round-robin.md)

*Service to Many Leads to Greatness.*
