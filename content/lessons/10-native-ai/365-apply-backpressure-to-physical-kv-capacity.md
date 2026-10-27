# Lesson 365 — Apply backpressure to physical KV capacity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Account for active and retained-idle K/V storage when memory pressure rises.

## Technical foundations

The K/V pool already distinguishes `reservedRawKvBytes` for active leases from `physicalRawKvBytes`, which includes retained idle allocations. The scheduler must use `Acquire` rather than implement a second budget calculator. If idle reuse is enabled, releasing a session may move memory from active to idle without reducing physical allocation. A later admission may reuse an idle store. The scheduler records pool counters for visibility but does not change them or create a shadow allocation policy.

## Worked scenario

With a 512-byte store size and a 1,024-byte physical budget, two active stores fill capacity. After A completes with idle retention enabled, active reservation falls to 512 bytes but physical allocation can remain 1,024 bytes. A future C may reuse A’s idle store, keeping physical allocation at the same level, while a third simultaneous active lease still cannot be admitted.

## Boundary conditions and failure modes

An admission check based solely on active bytes can underestimate retained idle storage. Conversely, automatically deleting idle stores on every release defeats the explicit retention policy. Both trade-offs belong to the existing pool service.

## Practical native Framework exercise

Inspect a scenario with two live leases, one release, one idle store reuse and final cancellation. Record active bytes, idle bytes and physical bytes after every transition.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Does the scheduler reduce KV bytes per model token?

<details><summary>Show worked answer</summary>

No. It controls when stores are reserved. The underlying cache geometry and FP32 storage remain unchanged.

</details>

## Mathematics connection

See [Unit 224](../11-maths-for-ai/224-reconcile-waiting-ready-and-in-flight-state.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](364-keep-scheduler-tickets-separate-from-kv-leases.md)

*Service to Many Leads to Greatness.*
