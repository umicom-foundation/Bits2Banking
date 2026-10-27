# Mathematics for AI — Unit 222: Order a FIFO queue independently of slot number

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

Use the monotonic submission sequence, not slot index. Slot numbers represent reusable storage positions; sequence numbers represent chronological admission priority. A recycled slot is not an earlier request.

## Fully worked example

A receives sequence 11 in slot 0, B sequence 12 in slot 1, C sequence 13 in slot 2. After B is cancelled, D takes slot 1 with sequence 14. The waiting order is A (11), C (13), D (14), regardless of sorted slot order [0,1,2]. If A has already been admitted, the next two waiting admissions are C then D.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** Sequence 5 is in slot 3; sequence 9 in slot 1; sequence 7 in slot 0. Which order is FIFO?

<details><summary>Reveal full worked solution</summary>

5 → 7 → 9.

</details>

## Discussion

Explain why the scheduler must not let a new request inherit the old occupant’s sequence.

## Connect to native AI engineering

[LLM Lesson 362](../10-native-ai/362-admit-queued-requests-in-fifo-order.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](221-calculate-effective-admission-capacity.md)

*Service to Many Leads to Greatness.*
