# Lesson 371 — Read scheduling counters without inventing latency claims

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Report queue state and reservation counters separately from inference timing.

## Technical foundations

The native inspection report exposes waiting, ready and dispatched counts as well as cumulative submissions, admissions, dispatches, acknowledgements, completions and cancellations. It also includes the pool’s active, idle and physically allocated raw K/V bytes. These values describe control-plane state at a point in time. They contain no timestamps, token embeddings, bandwidth measurements, prefill times or complete-generation latency distribution.

## Worked scenario

After submitting four requests and admitting two, an illustrative snapshot could show waiting=2, ready=2, dispatched=0 and activeRawKvBytes=1024. After dispatching one request, waiting remains 2, ready becomes 1 and dispatched becomes 1. The total number of bytes does not change because Dispatch does not allocate another cache. This says nothing about whether sampling takes 1 ms or 100 ms.

## Boundary conditions and failure modes

Avoid reporting requests/sec by dividing cumulative requests by an arbitrary clock interval without validating start/end boundaries and completions. Use the established native inference benchmark for controlled end-to-end elapsed times; record queue delays separately if a later timing extension is qualified.

## Practical native Framework exercise

Prepare two tables: one for scheduler counters and another for timed generation results. Explicitly label each unmeasured latency or throughput cell rather than substituting a work counter.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Can a totalDispatches counter alone establish tokens per second?

<details><summary>Show worked answer</summary>

No. A dispatch is an opportunity to execute a declared work unit, not a measured token or an elapsed duration.

</details>

## Mathematics connection

See [Unit 228](../11-maths-for-ai/228-calculate-warm-reuse-admission-under-pressure.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](370-coordinate-prefill-decode-and-rollover-phases.md)

*Service to Many Leads to Greatness.*
