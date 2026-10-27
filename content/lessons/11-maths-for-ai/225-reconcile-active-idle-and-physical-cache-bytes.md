# Mathematics for AI — Unit 225: Reconcile active, idle and physical cache bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

For this FP32 K/V pool, physical raw cache bytes include active plus retained idle allocations: `physicalRawKvBytes = reservedRawKvBytes + idleRawKvBytes`. This does not include pool object metadata, allocator headers, the model or the tape.

## Fully worked example

One store holds 512 bytes. Two are active and one is idle, so activeRawKvBytes=1,024, idleRawKvBytes=512 and physicalRawKvBytes=1,536. Reusing the idle store yields three active stores, zero idle and the same 1,536 physical bytes. Reuse does not imply that the physical allocation decreased.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** With one active 768-byte store and two idle stores of the same size, compute physical bytes.

<details><summary>Reveal full worked solution</summary>

Active=768; idle=1,536; physical=**2,304 bytes**.

</details>

## Discussion

Explain why checking only active bytes may misrepresent a memory-pressure situation.

## Connect to native AI engineering

[LLM Lesson 366](../10-native-ai/366-distinguish-bounded-queues-from-rejected-work.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](224-reconcile-waiting-ready-and-in-flight-state.md)

*Service to Many Leads to Greatness.*
