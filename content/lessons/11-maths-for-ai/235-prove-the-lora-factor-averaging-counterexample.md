# Mathematics for AI — Unit 235: Prove the LoRA factor-averaging counterexample

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **prove the lora factor-averaging counterexample**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Two rank-one scalar adapters represent the same update: A1=+1,B1=+1 and A2=−1,B2=−1.

## Full worked solution

Each true delta is B_i A_i=+1, so their mean delta is **1**. Separately averaged factors are A_bar=0 and B_bar=0, yielding B_bar A_bar=**0**. This violates correct delta averaging.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 383](../10-native-ai/383-aggregate-lora-updates-not-independent-factors.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** Would changing worker 2 to A2=+1,B2=−1 still give matching updates?

<details><summary>Reveal the full answer</summary>

No. Its delta becomes −1, so the true mean of +1 and −1 is **0**; the example’s matched-effect premise no longer holds.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
