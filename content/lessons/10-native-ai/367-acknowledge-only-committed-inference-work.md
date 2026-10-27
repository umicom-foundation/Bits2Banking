# Lesson 367 — Acknowledge only committed inference work

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Preserve logical progress when a model step fails after it has been dispatched.

## Technical foundations

A dispatched work record includes requested and completed logical step counts. `Acknowledge` increases the completed count only after the application confirms an independently committed operation. If that was the final step, the scheduler releases the existing pool lease first and only then invalidates the request ticket. For recoverable failures that have **not** committed decoder or KV changes, `ReturnUncommitted` returns the request to ready state without incrementing progress.

## Worked scenario

A needs two steps. A1 is dispatched, but a caller-owned decoding operation rejects an invalid input before mutating state. Returning A1 uncommitted leaves completedSteps at zero. A subsequent dispatch can retry A1 safely after correcting the input. When A1 succeeds, acknowledgement makes completedSteps equal one. A2’s successful acknowledgement releases the K/V lease.

## Boundary conditions and failure modes

Do not call ReturnUncommitted after sampling, appending K/V or publishing output if any part may have committed. This scheduler cannot roll back arbitrary application state. Retrying partially committed work could duplicate tokens or shift the checkpoint-bound cache incorrectly.

## Practical native Framework exercise

Trace both a clean rejection and a failure after a hypothetical partial model commit. State which branch may be retried and which requires application-level recovery rather than scheduler acknowledgement.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Why does the scheduler release the pool lease before marking the final request completed?

<details><summary>Show worked answer</summary>

If Release fails, the request still retains its lease and in-flight state. Marking it complete first would orphan resources or falsely report completion.

</details>

## Mathematics connection

See [Unit 225](../11-maths-for-ai/225-reconcile-active-idle-and-physical-cache-bytes.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](366-distinguish-bounded-queues-from-rejected-work.md)

*Service to Many Leads to Greatness.*
