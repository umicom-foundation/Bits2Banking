# Lesson 370 — Coordinate prefill, decode and rollover phases

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Locate the work stages that a scheduling primitive does not implement.

## Technical foundations

A scheduler can reserve a K/V store and grant a session work quantum, but the application must still prefill prompt projections through the canonical decoder, calculate valid logits, sample the next token and update accepted cache rows. During learned-absolute-position rollover, the existing full-context trace must rebuild all per-layer K/V projections. The scheduler should not reinterpret a work quantum as automatically corresponding to one cache append: a full-window step can require substantially different computation.

## Worked scenario

For context length four, prompt length two and four generated tokens, the first two growing-prefix transitions can reuse fixed earlier positions. Once the context is full, each subsequent shifted window must be recomputed for every layer in this model. A scheduler dispatches one application-defined unit per call; the application decides whether that unit performs prefill, a growing-prefix proposal, or a canonical rollover.

## Boundary conditions and failure modes

If a scheduler tries to shift cached K/V rows after eviction without recomputing learned positions, it violates the decoder contract. A generic queue should not embed shortcut rules about positional encoding or assume all model architectures permit the same reuse.

## Practical native Framework exercise

Draw the model state machine next to the scheduler state machine. Mark the full-window rebuild boundary separately from READY and DISPATCHED. Explain which transitions remain valid without a scheduler.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Does round-robin scheduling justify changing K/V rollover mathematics?

<details><summary>Show worked answer</summary>

No. Scheduling chooses when work is attempted, not how the established decoder calculates position-dependent attention.

</details>

## Mathematics connection

See [Unit 227](../11-maths-for-ai/227-understand-generation-count-identity-limits.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](369-construct-deterministic-scheduling-fixtures.md)

*Service to Many Leads to Greatness.*
