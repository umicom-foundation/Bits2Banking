# Lesson 376 — Complete a bounded multi-session scheduling capstone

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Combine memory admission, fairness, lifecycle validity and honest technical evidence in one repeatable lab.

## Technical foundations

Build a request timeline with three independent jobs and a pool that supports only two concurrently active K/V stores. Submit all jobs, admit the first pair, exercise cooperative dispatch until capacity is freed, then admit the oldest waiter. Record the exact dispatch sequence, ticket identities, pool counters and cancellation behaviour. Inspect correctness separately from performance: no accelerated attention path or simultaneous GPU inference is introduced here. A complete research report includes negative tests and the distinction between scheduler work units and committed model tokens.

## Worked scenario

Reference configuration: two Transformer layers, context length four, channels eight, FP32. A store reserves `2 × 2 × 4 × 8 × 4 = 512 bytes`; a 1,024-byte raw budget admits at most two such stores. Declare jobs A:2, B:2 and C:1. Admit A and B; the first four quanta alternate A/B. Once both complete, C is admitted and completes in one quantum. Report totalSubmissions=3, totalAdmissions=3, totalDispatches=5 and totalCompleted=3. Use the real pool’s observed memory counters for independent verification.

## Boundary conditions and failure modes

Do not label these five work quanta as five measured model tokens unless the application actually drives and verifies five successful decoder steps. Do not claim that RR selection proves fairness under varying execution time or that reuse produces a wall-clock speedup.

## Practical native Framework exercise

Write a six-part lab report: objectives, architecture, geometry, event trace, rejected calls and qualification limitations. Run tests on GCC/Clang and then qualify against the installed Windows Framework. Preserve original projects and alternative scripts.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** What constitutes a passing capstone?

<details><summary>Show worked answer</summary>

The exact FIFO and round-robin trace, correct pool budget and lease invalidation, zero unexpected state changes on rejections, and an explicit account of unrun full-integration or model tests.

</details>

## Mathematics connection

See [Unit 232](../11-maths-for-ai/232-complete-a-multi-session-admission-and-fairness-table.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](375-qualify-native-c23-scheduling-with-regression-tests.md)

*Service to Many Leads to Greatness.*
