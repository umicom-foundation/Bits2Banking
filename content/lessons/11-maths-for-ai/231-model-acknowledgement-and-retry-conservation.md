# Mathematics for AI — Unit 231: Model acknowledgement and retry conservation

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

Let r be the requested step budget and a the number of acknowledged steps for a live request. The remaining budget is r−a, where 0≤a≤r. A returned uncommitted quantum changes neither r nor a. A successful final acknowledgement removes the request and releases its lease.

## Fully worked example

A job requests r=4. After two successful acknowledgements a=2 and two quanta remain. The next Dispatch is returned uncommitted after a clean rejection: a stays 2. Later two successful acknowledgements raise a to 4, which finishes the job. Any scheme that incremented a on the failed attempt would declare completion after only three real successes.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** A job requests 5; 3 have been acknowledged and one later dispatch is returned uncommitted. How many successes remain?

<details><summary>Reveal full worked solution</summary>

5−3 = **2 acknowledged successes** remain.

</details>

## Discussion

Explain why scheduler-level retry cannot repair partially committed model or K/V state.

## Connect to native AI engineering

[LLM Lesson 374](../10-native-ai/374-preserve-checkpoint-and-tenant-boundaries-across-sessions.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](230-explain-why-serial-dispatch-is-not-tensor-batching.md)

*Service to Many Leads to Greatness.*
