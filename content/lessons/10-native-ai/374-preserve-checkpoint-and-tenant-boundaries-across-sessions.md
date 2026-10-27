# Lesson 374 — Preserve checkpoint and tenant boundaries across sessions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Describe why cache identity, account isolation and admission need separate controls.

## Technical foundations

A K/V pool is configured for one specified stacked-model geometry and checkpoint digest, and its stores inherit that configuration. The scheduler borrows one pool; it is not a general multi-model registry. Applications must still verify the live model’s canonical checkpoint identity and preserve tenant-specific controls outside this bounded teaching API. Request IDs and queue tickets are operational handles, not authentication tokens, financial-account authorisations or privacy policy decisions.

## Worked scenario

Imagine a serving process with model checkpoint M1 and M2. Because cached key/value projections depend on weights, an M1 K/V store cannot be silently reused for M2. A separate pool, or a thoroughly verified replacement lifecycle, is required. Even if context length and channels happen to match, the digest mismatch must reject reuse.

## Boundary conditions and failure modes

The scheduler alone cannot prove that a caller is authorised to submit a tenant request. It has no network authentication, per-tenant encryption, data-retention policy, or secure erasure contract. Those are separate Framework and deployment responsibilities.

## Practical native Framework exercise

Write a responsibility matrix for identity of the decoder checkpoint, validity of a K/V lease, queue-ticket freshness, tenant authorisation and audit logging.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Does knowing a valid scheduler ticket authorise a caller to access another tenant’s prompt?

<details><summary>Show worked answer</summary>

No. A ticket identifies queue work only; it does not confer security privileges or expose another tenant’s K/V data.

</details>

## Mathematics connection

See [Unit 230](../11-maths-for-ai/230-explain-why-serial-dispatch-is-not-tensor-batching.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](373-prevent-aba-errors-during-scheduler-slot-reuse.md)

*Service to Many Leads to Greatness.*
