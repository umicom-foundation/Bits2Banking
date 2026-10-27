# Mathematics for AI — Unit 232: Complete a multi-session admission and fairness table

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

Combine queue capacity, K/V geometry and dispatch order in one bounded exercise. Count both control-plane state transitions and raw K/V allocations; avoid conflating them with elapsed time or neural token outputs.

## Fully worked example

Reference example: L=2, T=4, C=8, FP32 yields S=2×2×4×8×4=512 bytes. With budget 1,024, at most two K/V stores are active. A:2, B:2 and C:1 are submitted; A and B admitted, C waiting. Four successful quanta follow A,B,A,B. A and B complete and free their leases. Admit C and acknowledge C: total submissions=3, total admissions=3, total acknowledgements=5, total completed=3. At peak active raw K/V bytes=1,024.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** Change the scenario so A:1, B:3 and C:2. If C can only be admitted after one of the first two finishes, list a valid dispatch sequence and the peak active cache bytes.

<details><summary>Reveal full worked solution</summary>

One valid sequence is A,B,C,B,C,B if C is admitted immediately after A completes and scanning follows slot order; total six successful quanta. Peak active raw K/V remains **1,024 bytes**.

</details>

## Discussion

Check the exact slot rotation rule when deriving an interleaving. Other valid sequences can arise from different admission timing; each must respect an explicit policy.

## Connect to native AI engineering

[LLM Lesson 375](../10-native-ai/375-qualify-native-c23-scheduling-with-regression-tests.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](231-model-acknowledgement-and-retry-conservation.md)

*Service to Many Leads to Greatness.*
