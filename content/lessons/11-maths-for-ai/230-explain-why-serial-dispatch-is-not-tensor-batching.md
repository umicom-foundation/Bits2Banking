# Mathematics for AI — Unit 230: Explain why serial dispatch is not tensor batching

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

A scheduler can interleave requests without evaluating a shared matrix kernel across multiple sequences. In tensor batching, activations may have a batch dimension B and per-step compute may exploit vectorised hardware. In serial scheduling, each decoder operation remains separate even if the request order changes.

## Fully worked example

If two independent model calls each take 12 ms and scheduling overhead is 1 ms per call, serial dispatch takes roughly 26 ms. Hypothetically a true batched implementation might take 17 ms for both, but that number is a made-up scenario, not a result of this scheduler. The correct conclusion is only that batching would require different model execution contracts.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** A serial runner executes three 6-ms calls with 1 ms overhead each. Estimate total elapsed time.

<details><summary>Reveal full worked solution</summary>

3×(6+1) = **21 ms** under these simplifying assumptions.

</details>

## Discussion

Explain why the existence of a request queue does not prove parallel GPU utilisation.

## Connect to native AI engineering

[LLM Lesson 373](../10-native-ai/373-prevent-aba-errors-during-scheduler-slot-reuse.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](229-distinguish-step-fairness-from-service-rate.md)

*Service to Many Leads to Greatness.*
