# Lesson 361 — Separate scheduling from Transformer execution

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Language:** Native C23 · **Prerequisites:** Lessons 329–360 and Mathematics Unit 221.

## Learning outcome

Explain which parts of an inference-serving request belong to a scheduler and which remain the responsibility of the decoder and K/V store.

## Technical foundations

The scheduler maintains request eligibility and *declared work units*. A submitted request is waiting, an admitted request holds a genuine Framework K/V pool lease, and a dispatched request temporarily owns the next cooperative quantum. The scheduler never computes embeddings, softmax, vocabulary logits or nucleus sampling. Those operations remain with the established stacked decoder and its inference session. The caller must acknowledge only **after** it has committed one valid logical step. The new API therefore provides a deterministic coordination primitive, not a claim of batched GPU execution.

## Worked scenario

Suppose request A needs two logical steps and request B needs one. Admission obtains two leases if the physical K/V budget allows. Dispatch can return A, B, A in round-robin order; the calling application performs A1, B1 and A2 using its own verified decoder state. B releases its lease after B1 and A releases its lease after A2. No token output is synthesised by the scheduler.

## Boundary conditions and failure modes

An application that acknowledges before the decoder commits can silently lose a token when the computation fails. An application that calls a decoder concurrently on a caller-serialised tape can corrupt an otherwise valid trace. Scheduler readiness is not a licence for concurrent model access.

## Practical native Framework exercise

Draw separate boxes for request scheduling, lease storage and neural computation. Mark who owns the model and who must certify that a token has been committed. Identify which box is allowed to reset retained KV state.

### Relevant native interfaces

The established `UmiAiTrainingStackedKvPool` owns K/V allocations. The additive `UmiAiTrainingStackedKvScheduler` manages queue metadata, admission and cooperative dispatch; its `Dispatch` result is **not** a sampled token. Use `UmiAiTrainingStackedKvSchedulerSubmit`, `AdmitNext`, `Dispatch` and `Acknowledge` under the borrowed-pool lifetime contract. Correct model execution remains inside the canonical stacked decoder and its K/V services.

## Check your understanding

**Question:** Why is a successful Dispatch not evidence that one token has been generated?

<details><summary>Show worked answer</summary>

Dispatch only grants a work opportunity and returns a lease. An independent decoder operation must succeed and commit before Acknowledge is appropriate.

</details>

## Mathematics connection

See [Unit 221](../11-maths-for-ai/221-calculate-effective-admission-capacity.md).

## External research for context

- [Orca: iteration-level scheduling for Transformer serving (OSDI 2022)](https://www.usenix.org/conference/osdi22/presentation/yu)
- [vLLM: PagedAttention and LLM serving (2023)](https://arxiv.org/abs/2309.06180)

## Continue learning

[HTML study route](../../courses/llm-from-scratch/kv-scheduling-learning-path.html) · [Previous lesson](360-capstone-native-lease-reuse-and-evidence.md)

*Service to Many Leads to Greatness.*
