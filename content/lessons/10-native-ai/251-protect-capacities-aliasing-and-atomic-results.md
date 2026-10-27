# Lesson 251 — Protect capacities, aliasing and atomic results

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Course:** Building an LLM from Scratch · **Implementation language:** C23

**Learning objective:** Understand the C23 memory contract for safe inference calls.

## 1. Understand the concept

A native function that accepts raw pointers must distinguish logical size from the amount of accessible storage. `channels` describes the query and output vector. `validRows × channels` describes each K/V buffer. `headCount` must be positive and divide `channels`. Before multiplication, check `validRows <= LIMIT / channels` to prevent size overflow.

For a function promising failure-atomic results, it is insufficient to return an error after overwriting the first few output floats. Compute into private scratch, validate every element and publish only after all heads succeed. Also reject overlapping writable output and input regions unless the algorithm is explicitly designed for in-place operation. Immutable inputs may share storage with one another if all are merely read.

## 2. Work through the numbers

Suppose a call needs `4 × 8 = 32` K elements and 32 V elements. The user supplies `keyCapacity=31`, `valueCapacity=32` and a four-float output prefilled with `[-1,-1,-1,-1]`. A valid contract returns a capacity error before any reads of the missing element. It leaves all four output values unchanged. If the candidate additionally exposes a statistics record, that record should also remain unchanged after rejection.

Now consider `validRows=SIZE_MAX` and `channels=8`: multiplying before checking would wrap in unsigned arithmetic. Checking the division bound first avoids treating an enormous request as a tiny allocation.

## 3. Apply the concept to native model engineering

The native unit tests exercise invalid head counts, insufficient output capacity, non-finite scores, aliasing and an oversized request. Inspect the output sentinel values before and after the call. Distinguish `UMI_STATUS_INVALID_ARGUMENT` for malformed requests from `UMI_STATUS_CAPACITY_EXCEEDED` for undersized buffers.

`malloc` failures are part of the error contract; allocator failure injection and concurrency misuse require additional environment-specific testing. Calling the kernel with a pointer that does not designate an accessible array is undefined behaviour before any function can make it safe.

## 4. Check the mathematical foundation

The related exercise is [Mathematics for AI — Unit 138](../11-maths-for-ai/138-calculate-a-weighted-value-vector.md). Work out the arithmetic independently before inspecting an implementation.

## 5. Test your understanding

**Question:** Why should a calculation publish its output once rather than after each attention head?

<details>
<summary>Reveal the worked answer</summary>
<p>A later head may fail because of a non-finite result or memory error. A single publication point prevents a partially updated output vector.</p>
</details>

## 6. Key distinctions

The mathematical examples are deliberately small and inspectable. Changes to attention topology, positional schemes, quantisation and decoding policy require explicit model or algorithm contracts. A standalone operator test does not establish complete Transformer equivalence or measured inference acceleration.

## Continue learning

[250 — Compare a kernel against the canonical last row](250-compare-a-kernel-against-the-canonical-last-row.md) · [252 — Separate prefill from incremental decode](252-separate-prefill-from-incremental-decode.md) · [HTML learning path](../../courses/llm-from-scratch/efficient-decoding-learning-path.html)

*Service to Many Leads to Greatness.*
