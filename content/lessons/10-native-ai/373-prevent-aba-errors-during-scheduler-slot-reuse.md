# Lesson 373 — Prevent ABA errors during scheduler slot reuse

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Apply owner IDs and generation numbers across repeated request lifetimes.

## Technical foundations

The ABA problem occurs when a slot appears to return to its old state after being released and reassigned. A slot index is therefore insufficient proof of ownership. The scheduler records a generation for every slot and a distinct scheduler identity for every instance. A ticket is accepted only if the owner identity, slot and generation all agree with a currently live entry. This is separate from the K/V pool’s own generation-stamped lease checks.

## Worked scenario

Request A occupies scheduler slot 0 with generation 1. It completes, and request C later reuses slot 0 with generation 2. The old A ticket cannot cancel C. Likewise, destroying one scheduler and creating another must not permit its tickets to be interpreted as belonging to the new scheduler if memory addresses happen to be reused.

## Boundary conditions and failure modes

A monotonic identifier has a finite range. The native implementation refuses generation or owner ID exhaustion rather than wrapping back into an earlier identity. An application must not serialise raw ticket bytes as durable identity or assume process-local counters survive restart.

## Practical native Framework exercise

Create a stale ticket, complete its request, submit another using the same slot and attempt Cancel with the stale ticket. Repeat using two different scheduler instances.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Why are poolIdentity and schedulerIdentity different fields?

<details><summary>Show worked answer</summary>

A queued request and a K/V allocation have different owners and lifetimes. Their identity checks are independent.

</details>

## Mathematics connection

See [Unit 230](../11-maths-for-ai/230-explain-why-serial-dispatch-is-not-tensor-batching.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](372-reason-about-fairness-and-starvation-limits.md)

*Service to Many Leads to Greatness.*
