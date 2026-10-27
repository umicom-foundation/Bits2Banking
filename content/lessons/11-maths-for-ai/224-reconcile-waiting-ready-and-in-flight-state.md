# Mathematics for AI — Unit 224: Reconcile waiting, ready and in-flight state

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

At every snapshot, each live scheduler request occupies exactly one of WAITING, READY or DISPATCHED. Let W, R and F be those counts. Then live requests = W+R+F. The single-in-flight contract restricts F to 0 or 1.

## Fully worked example

Suppose seven jobs were submitted historically, two completed and one cancelled. Four remain live. An inspection with W=2, R=1 and F=1 is consistent because 2+1+1=4. A report claiming F=2 violates the single in-flight contract even if the historic submission total is large.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** If 12 were submitted, 4 completed and 3 cancelled, how many remain? Give a valid W/R/F breakdown.

<details><summary>Reveal full worked solution</summary>

12−4−3=**5** remain; for example W=3,R=1,F=1.

</details>

## Discussion

Note that totalAdmitted can exceed the current number of ready sessions because completed requests are counted historically.

## Connect to native AI engineering

[LLM Lesson 365](../10-native-ai/365-apply-backpressure-to-physical-kv-capacity.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](223-derive-round-robin-dispatch-sequences.md)

*Service to Many Leads to Greatness.*
