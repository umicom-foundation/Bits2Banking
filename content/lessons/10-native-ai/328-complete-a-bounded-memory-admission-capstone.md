# Lesson 328 — Complete a bounded memory admission capstone

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** LLM · Native AI systems

## Learning objective

Combine capacity estimates with independent numerical qualification.

## Technical foundation

Create three workloads: small single-session, near-budget multi-session and an intentional overflow. Record checkpoint identifier, dimensions, precision, expected raw K/V bytes, available budget and admission. For actual inference, separately run canonical full-logit tests before any performance comparison.

A useful analysis distinguishes a mathematical capacity estimate from memory actually allocated by an application. The former follows a declared model geometry and scalar width; the latter requires an allocator or runtime measurement. Cache correctness must also be qualified against the canonical decoder's checkpoint, position semantics and full vocabulary logits.

## Worked investigation

Take the numerical quantities in the example above and identify the number of layers, token positions, attention heads, scalar elements and bytes. Change one input while preserving the others. Recalculate the answer and explain why the result is linear in that dimension. When no unit appears in an equation, introduce it explicitly before comparing results.

## Native C23 connection

The Umicom Framework provides `UmiAiTrainingInferenceMemoryPlan` as a bounded estimator of raw K/V memory. It takes explicit tensor geometry and a cache budget, rejects invalid head ratios or overflow, and publishes a complete report only after validation. The planner neither trains a model nor allocates a KV cache. The established stacked decoder, K/V store and numerical qualification services remain the sources of truth for actual inference.

## Exercise

**Question:** Is a passing memory-planner test sufficient evidence of decoder correctness?

<details><summary>Reveal worked answer</summary>

No; it checks only arithmetic and capacity policy, not actual neural inference.

</details>

## Further exploration

Compare a second configuration and state which conditions must remain the same for a fair comparison. Investigate what temporary allocation, paging metadata or ownership state might be absent from a simple raw-payload estimate. Record any unmeasured behaviour as unmeasured rather than inferred.

## Continue learning

[Browser learning path](../../courses/llm-from-scratch/kv-memory-admission-learning-path.html) · [Companion course](../../courses/maths-for-ai/kv-memory-admission-mathematics.html)

*Service to Many Leads to Greatness.*
