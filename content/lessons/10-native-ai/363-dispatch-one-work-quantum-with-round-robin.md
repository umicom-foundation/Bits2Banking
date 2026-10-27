# Lesson 363 — Dispatch one work quantum with round robin

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Predict cooperative scheduling order and understand its fairness assumptions.

## Technical foundations

After admission, a ready request can receive exactly one work quantum. `Dispatch` rotates across slot positions, skipping empty, waiting and already-dispatched entries. A single outstanding quantum is allowed per scheduler, so the caller must acknowledge or return it uncommitted before another dispatch. This avoids hidden threading, context switching and ownership changes. It is a deliberate teaching service rather than an operating-system or distributed inference scheduler.

## Worked scenario

Two admitted sessions A and B each request three steps. Assuming both are initially ready and every step succeeds, dispatch order is A, B, A, B, A, B. A session that finishes is removed before the next selection. If a third session C becomes ready halfway through, it joins later rotations; no completed step is retroactively reordered.

## Boundary conditions and failure modes

A round-robin dispatcher cannot guarantee equal *time* per request if one decoder step takes 50 ms and another takes 5 ms. Nor does it offer preemption: a blocking application may monopolise the single in-flight quantum. Uniform logical quanta are not uniform computational cost.

## Practical native Framework exercise

Simulate three requests of lengths [2,1,3]. Write the slot selected on each dispatch and the remaining steps after each acknowledgement. Explain the order when the one-step request releases its lease.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Why is this not continuous GPU batching?

<details><summary>Show worked answer</summary>

It selects work sequentially using K/V leases; it does not form a shared tensor batch or execute multiple model graphs together.

</details>

## Mathematics connection

See [Unit 222](../11-maths-for-ai/222-order-a-fifo-queue-independently-of-slot-number.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](362-admit-queued-requests-in-fifo-order.md)

*Service to Many Leads to Greatness.*
