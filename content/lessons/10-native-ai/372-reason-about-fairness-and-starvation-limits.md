# Lesson 372 — Reason about fairness and starvation limits

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Identify exactly what bounded round robin guarantees and what it does not.

## Technical foundations

If every dispatched work unit is eventually acknowledged or returned and all ready requests remain eligible, the scheduler rotates across ready slots and does not repeatedly choose the same slot ahead of another ready slot. It does not guarantee a maximum *time* to service: one in-flight operation may block arbitrarily long, and admission itself is limited by K/V capacity. FIFO controls the order in which waiting requests obtain leases, not the order in which requests complete.

## Worked scenario

Two ready sessions A and B each hold a lease. A requires three quanta and B one. Under successful cooperative dispatch the order A, B, A, A completes B early. Now suppose the caller spends a full second on A’s first quantum and 5 ms on B’s; B waits for the slower operation even though the selection sequence is fair by quanta.

## Boundary conditions and failure modes

A high-priority request class, deadline scheduler or multi-worker service would require a separate policy and real concurrency qualification. Adding a request identifier field does not imply that the scheduler implements priorities, preemption or service-level objectives.

## Practical native Framework exercise

State assumptions needed for eventual service: admitted sessions remain runnable, each dispatched quantum returns, and clients continue calling Dispatch. Give one counterexample for each missing assumption.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** What is the most important fairness limitation of the current scheduler?

<details><summary>Show worked answer</summary>

It is cooperative and non-preemptive: a stalled in-flight operation can delay every other request regardless of rotation.

</details>

## Mathematics connection

See [Unit 229](../11-maths-for-ai/229-distinguish-step-fairness-from-service-rate.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](371-read-scheduling-counters-without-inventing-latency-claims.md)

*Service to Many Leads to Greatness.*
