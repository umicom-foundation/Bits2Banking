# Mathematics for AI — Unit 228: Calculate warm reuse admission under pressure

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

Idle retention can avoid a fresh heap allocation but cannot create additional capacity beyond the pool budget. Under a fixed physical allocation, reassignment from idle to active changes the category of bytes without changing their total.

## Fully worked example

Two 512-byte stores exist under a 1,024-byte raw budget. One is active and one idle. Reuse the idle store: active rises from 512 to 1,024, idle drops from 512 to zero and physical remains 1,024. A third active request cannot be admitted without a release, regardless of how fast allocations appear.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** Given three physical 256-byte stores (one active, two idle), reuse both. What are active and physical bytes afterwards?

<details><summary>Reveal full worked solution</summary>

Active becomes 3×256 = **768 bytes**; physical stays **768 bytes**.

</details>

## Discussion

Identify which transitions would require new allocation and which can use retained idle storage.

## Connect to native AI engineering

[LLM Lesson 370](../10-native-ai/370-coordinate-prefill-decode-and-rollover-phases.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](227-understand-generation-count-identity-limits.md)

*Service to Many Leads to Greatness.*
