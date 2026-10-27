# Mathematics for AI — Unit 195 — Apply absolute relative numerical tolerance

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Study area:** Mathematics for AI · Native AI systems

## Learning objective

Evaluate a declared error criterion.

## Technical foundation

For reference 2.0, candidate 2.0003, absolute tolerance 0.0001 and relative tolerance 0.0002, allowed deviation is 0.0001+0.0002×2=0.0005; observed deviation 0.0003 passes.

A useful analysis distinguishes a mathematical capacity estimate from memory actually allocated by an application. The former follows a declared model geometry and scalar width; the latter requires an allocator or runtime measurement. Cache correctness must also be qualified against the canonical decoder's checkpoint, position semantics and full vocabulary logits.

## Worked investigation

Take the numerical quantities in the example above and identify the number of layers, token positions, attention heads, scalar elements and bytes. Change one input while preserving the others. Recalculate the answer and explain why the result is linear in that dimension. When no unit appears in an equation, introduce it explicitly before comparing results.

## Native C23 connection

The Umicom Framework provides `UmiAiTrainingInferenceMemoryPlan` as a bounded estimator of raw K/V memory. It takes explicit tensor geometry and a cache budget, rejects invalid head ratios or overflow, and publishes a complete report only after validation. The planner neither trains a model nor allocates a KV cache. The established stacked decoder, K/V store and numerical qualification services remain the sources of truth for actual inference.

## Exercise

**Question:** Does an observed difference of 0.0006 pass this example?

<details><summary>Reveal worked answer</summary>

No; it exceeds 0.0005.

</details>

## Further exploration

Compare a second configuration and state which conditions must remain the same for a fair comparison. Investigate what temporary allocation, paging metadata or ownership state might be absent from a simple raw-payload estimate. Record any unmeasured behaviour as unmeasured rather than inferred.

## Continue learning

[Browser learning path](../../courses/maths-for-ai/kv-memory-admission-mathematics.html) · [Companion course](../../courses/llm-from-scratch/kv-memory-admission-learning-path.html)

*Service to Many Leads to Greatness.*
