# Lesson 375 — Qualify native C23 scheduling with regression tests

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Create a test matrix for admission, round robin, stale tickets and memory pressure.

## Technical foundations

The new Framework library is registered through `cmake/UmicomAiStackedKvScheduler.cmake`, which links to the established K/V pool instead of recompiling its source. Tests should link against this canonical target and exercise: FIFO order after slot reuse; actual `CAPACITY_EXCEEDED` when the pool is full; successful acquisition after release; round-robin dispatch sequence; in-flight cancellation rejection; valid uncommitted returns; stale/cross-owner tickets; and unchanged outputs on rejected requests. Compile with C23 and strict warnings on the supported toolchains.

## Worked scenario

A sample deterministic test creates a pool for two sessions and a scheduler for three requests. It queues three jobs, admits two, confirms the third admission is blocked, completes the first pair and admits the waiter. One scheduling test uses five declared quanta total; its expected `totalAcknowledgedSteps` value is five. Repeat the test with idle-store retention enabled to verify warm reuse does not change admission fairness.

## Boundary conditions and failure modes

Sanitizer execution catches some memory hazards but does not by itself prove correctness of actual Transformer logits. Controlled store doubles are useful for isolating the scheduler; they must be distinguished in reports from tests linked to the full Framework build and real production K/V store.

## Practical native Framework exercise

Construct a verification table with columns test name, unit/integration scope, toolchain, result and remaining risk. Include at least one stale-ticket failure and one in-flight cancellation refusal.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Which two categories of testing are needed before declaring the new service integrated?

<details><summary>Show worked answer</summary>

Isolated scheduler tests and complete Framework tests linked to the real K/V store and decoder lifecycle. The first does not substitute for the second.

</details>

## Mathematics connection

See [Unit 231](../11-maths-for-ai/231-model-acknowledgement-and-retry-conservation.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](374-preserve-checkpoint-and-tenant-boundaries-across-sessions.md)

*Service to Many Leads to Greatness.*
