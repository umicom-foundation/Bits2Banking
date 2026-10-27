# Mathematics for AI — Unit 221: Calculate effective admission capacity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

Admission is bounded by the scheduler request count, the pool active-session limit and the raw physical K/V budget. With no other allocations or constraints, an upper bound on simultaneous admissions is `min(R, P, floor(B / S))`, where R is queued/ready request metadata capacity, P is pool session slots, B is the raw KV budget and S is full-session raw KV bytes. The bound is not necessarily achievable if idle allocations or unrelated slots are occupied.

## Fully worked example

If R=8, P=3, S=512 bytes and B=1,024 bytes, the budget accommodates floor(1024/512)=2 stores, so the upper bound is min(8,3,2)=**2**. A third request may remain queued. If budget B is the pool’s documented unlimited value zero, omit the floor term rather than using floor(0/S)=0.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** Set R=10, P=4, B=2,560 and S=512. What is the maximum simultaneously admitted count before considering existing idle stores?

<details><summary>Reveal full worked solution</summary>

min(10,4,floor(2560/512)) = min(10,4,5) = **4**.

</details>

## Discussion

State why metadata queue capacity and actual reserved cache bytes are different quantities.

## Connect to native AI engineering

[LLM Lesson 361](../10-native-ai/361-separate-scheduling-from-transformer-execution.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](220-complete-a-cache-reuse-accounting-table.md)

*Service to Many Leads to Greatness.*
