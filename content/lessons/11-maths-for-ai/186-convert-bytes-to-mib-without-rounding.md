# Mathematics for AI — Unit 186 — Convert bytes to mib without rounding

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Mathematics for AI · Native AI systems

## Learning objective

Use binary units consistently.

## Technical foundation

One MiB is 1,048,576 bytes. 25,165,824 bytes ÷ 1,048,576 = 24 MiB. One MB is instead 1,000,000 bytes.

A useful analysis distinguishes a mathematical capacity estimate from memory actually allocated by an application. The former follows a declared model geometry and scalar width; the latter requires an allocator or runtime measurement. Cache correctness must also be qualified against the canonical decoder's checkpoint, position semantics and full vocabulary logits.

## Worked investigation

Take the numerical quantities in the example above and identify the number of layers, token positions, attention heads, scalar elements and bytes. Change one input while preserving the others. Recalculate the answer and explain why the result is linear in that dimension. When no unit appears in an equation, introduce it explicitly before comparing results.

## Native C23 connection

The Umicom Framework provides `UmiAiTrainingInferenceMemoryPlan` as a bounded estimator of raw K/V memory. It takes explicit tensor geometry and a cache budget, rejects invalid head ratios or overflow, and publishes a complete report only after validation. The planner neither trains a model nor allocates a KV cache. The established stacked decoder, K/V store and numerical qualification services remain the sources of truth for actual inference.

## Exercise

**Question:** How many MiB are 2,097,152 bytes?

<details><summary>Reveal worked answer</summary>

2 MiB.

</details>

## Further exploration

Compare a second configuration and state which conditions must remain the same for a fair comparison. Investigate what temporary allocation, paging metadata or ownership state might be absent from a simple raw-payload estimate. Record any unmeasured behaviour as unmeasured rather than inferred.

## Continue learning

[Browser learning path](../../courses/maths-for-ai/kv-memory-admission-mathematics.html) · [Companion course](../../courses/llm-from-scratch/kv-memory-admission-learning-path.html)

*Service to Many Leads to Greatness.*
