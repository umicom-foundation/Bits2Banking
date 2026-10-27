# Mathematics for AI — Unit 223: Derive round-robin dispatch sequences

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

A cooperative round robin cycles over ready sessions, granting at most one declared work quantum before rotation. Requests finishing earlier leave the rotation. The number of dispatches required for successful completion is the sum of requested steps, not the number of requests.

## Fully worked example

A has 3 steps, B has 1 and C has 2. With slot order A,B,C and all admitted, the dispatch sequence is A,B,C,A,C,A. Totals are A=3, B=1, C=2 and 6 dispatches. B disappears after its first quantum. This is a sequence identity only; actual elapsed times might differ widely.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** For A=2 and B=3 with A first, list the complete sequence.

<details><summary>Reveal full worked solution</summary>

A,B,A,B,B — five dispatches.

</details>

## Discussion

Why does alternation over work units not guarantee equal CPU time?

## Connect to native AI engineering

[LLM Lesson 363](../10-native-ai/363-dispatch-one-work-quantum-with-round-robin.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](222-order-a-fifo-queue-independently-of-slot-number.md)

*Service to Many Leads to Greatness.*
