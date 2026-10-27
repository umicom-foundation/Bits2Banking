# Lesson 362 — Admit queued requests in FIFO order

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Use submission order, not recycled slot position, to select the oldest waiting session.

## Technical foundations

Submission is allocation-free with respect to K/V memory: it reserves only bounded scheduler metadata. Admission is a separate call to the existing `UmiAiTrainingStackedKvPoolAcquire`. The request with the smallest live submission sequence number is selected. If the pool cannot admit a new lease because its session count or physical memory budget is exhausted, the request stays in the waiting state; there is no partial queue publication. This distinction lets the application manage backpressure without pretending that unlimited simultaneous K/V reservations exist.

## Worked scenario

Three requests arrive A, B, C. A is assigned slot 0, B slot 1, and C slot 2. If B is cancelled before admission, a later D can occupy slot 1. Even though D has a numerically smaller slot than C, admission must choose C before D because C submitted earlier. The scheduler uses its monotonic submission order, not a scan for the smallest slot index.

## Boundary conditions and failure modes

Do not interpret FIFO admission as FIFO finishing. A request needing ten steps can finish after a later one-step request. Also do not treat `CAPACITY_EXCEEDED` as a permanently rejected request: the queued entry remains eligible after another lease is released.

## Practical native Framework exercise

Create requests with identifiers 10, 20 and 30. Cancel 20, submit 40, then list the exact order in which `AdmitNext` should obtain leases. Test a full pool and confirm the queue state is unchanged.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** What is the difference between Submit success and AdmitNext success?

<details><summary>Show worked answer</summary>

Submit records bounded waiting work. AdmitNext successfully acquires the canonical K/V lease and turns one waiting request into a ready one.

</details>

## Mathematics connection

See [Unit 221](../11-maths-for-ai/221-calculate-effective-admission-capacity.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](361-separate-scheduling-from-transformer-execution.md)

*Service to Many Leads to Greatness.*
