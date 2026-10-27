# Mathematics for AI — Unit 229: Distinguish step fairness from service rate

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Prerequisite:** Units 209–220 and basic arithmetic.

## Learning objective

If all successful request work quanta have duration d, a fully busy single dispatcher can complete at most about 1/d quanta per second, excluding scheduling overhead. Real inference quanta are variable, so a step counter by itself cannot establish throughput.

## Fully worked example

A hypothetical system performs 100 quanta of exactly 10 ms each sequentially. Idealised total quantum time is 1,000 ms and upper-bound rate is 100 quanta/s before overhead. If half of the quanta instead take 40 ms, the total is 50×10+50×40=2,500 ms and the corresponding idealised rate is 40 quanta/s.

## Mathematical scope

Numbers and rates in these examples are illustrative. A KV payload estimate excludes allocator overhead, model parameters, activation tensors and process memory. A counted scheduler work unit is not automatically a model-generated token.

## Exercise

**Question:** For 20 quanta of 5 ms and 10 quanta of 15 ms, compute total quantum time and idealised rate.

<details><summary>Reveal full worked solution</summary>

Total=20×5+10×15=**250 ms** for 30 quanta; idealised rate=**120 quanta/s**, excluding overhead.

</details>

## Discussion

Neither of these idealised rates is measured token throughput unless each quantum commits exactly one model token.

## Connect to native AI engineering

[LLM Lesson 371](../10-native-ai/371-read-scheduling-counters-without-inventing-latency-claims.md) explains the corresponding Framework ownership and scheduling contracts. Reusable calculations belong to the native Framework rather than an application-specific script.

## Continue learning

[HTML study route](../../courses/maths-for-ai/kv-scheduling-mathematics.html) · [Previous unit](228-calculate-warm-reuse-admission-under-pressure.md)

*Service to Many Leads to Greatness.*
