# Mathematics for AI — Unit 18: Memory Budgets and Safe Rollback

**Bits to Banking · Umicom Foundation · Sammy Hegab**

## Learning outcome

Distinguish memory currently retained from the historical maximum, calculate whether a requested allocation fits a budget, and understand why a failed computation must not publish incomplete results.

## 1. Storage has an explicit limit

Every numerical tensor consumes storage. A training tape may also retain gradients, operation metadata, attention probabilities and saved intermediate results required for the backward pass. Unbounded graph growth would eventually exhaust memory even if individual calculations were correct.

A useful admission rule is:

`currentBytes + requestedBytes ≤ budgetBytes`

The inequality means the requested operation fits only if the new total is no greater than the declared limit. Real implementations must check for integer overflow **before** adding the two values.

Example: current retained storage is 1,200 bytes, a new operation needs 600 bytes and the budget is 1,900 bytes. The new total is 1,800 bytes, so the allocation is admissible. If the request needs 800 bytes, the new total would be 2,000 bytes and should be rejected.

## 2. Current storage is not peak storage

Suppose allocations rise from 1,200 bytes to 1,800 bytes and then return to 1,200 after a rollback. The current amount is again 1,200. The historical peak remains **1,800 bytes**. A high peak is evidence of past usage; it is not automatically a leak.

A **memory leak** occurs when allocated storage is unintentionally retained or becomes unreachable without being released. Repeating the same operation and checking that current allocation returns to a stable level is useful evidence; external tools such as AddressSanitizer remain important.

## 3. Rollback is a transaction for temporary graph nodes

Consider a four-stage graph construction. Stage three fails due to insufficient capacity. A safe operation must release nodes created by stages one and two of that attempted operation, retain the pre-existing graph and refuse to publish an incomplete result.

The Framework exposes `UmiAiTrainingTapeCheckpoint` to capture a graph position and `UmiAiTrainingTapeRollback` to remove a suffix. `UmiAiTrainingTapeRewind` can additionally reset an iteration to its retained leaf prefix. Their ownership and validity rules belong to the Framework, not to individual Bits2Banking examples.

## 4. Why this matters for repeated fine-tuning

A training step temporarily creates forward outputs and a loss tensor. If the graph is never rolled back, the next training step would accumulate another graph alongside the first. Eventually a small educational model could fail even though its **parameter count** had not grown.

The Framework's low-rank supervised-step capability uses a checkpoint around its forward/backward operations. The two adapter matrices remain as trainable leaves, the frozen projection remains untouched, and the temporary graph is released after each step. An unsuccessful update must not return a fabricated successful loss report.

**Scope:** This graph-memory budget accounts for retained tape allocations, not total process RSS, device memory or temporary allocator metadata.

## 5. A memory-inspection excerpt

```c
UmiAiTrainingTapeMemory memory = {0};
UmiStatus status = UmiAiTrainingTapeMemoryInspect(tape, &memory);
if (status == UMI_STATUS_OK) {
    /* Inspect memory.currentBytes, memory.peakBytes and memory.budgetBytes. */
}
```

The code is illustrative and expects a valid Framework tape created elsewhere. It does not allocate its own tensor implementation.

## Practice and answers

1. Current 1,250 bytes; request 900; budget 2,000. **Reject:** 2,150 exceeds the budget.
2. Peak 1,900 before rollback; current returns to 1,250. **Peak remains 1,900**.
3. Why should a failed public operation preserve the result pointer or structure? **To stop callers from using incomplete or misleading state as if it were valid**.

Use the [illustrated HTML unit](../../courses/maths-for-ai/lessons/18-memory-budgets-and-rollback.html) for the memory timeline and additional exercises.
