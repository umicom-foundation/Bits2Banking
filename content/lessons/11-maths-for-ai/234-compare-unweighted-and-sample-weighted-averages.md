# Mathematics for AI — Unit 234: Compare simple and sample-weighted means

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **compare simple and sample-weighted means**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Use the three local endpoint weights 1.050, 0.990 and 1.080.

## Full worked solution

The simple mean is (1.050+0.990+1.080)/3 = **1.040**. With counts 100, 250 and 150, the sample-weighted mean is (105+247.5+162)/500 = **1.029**. Different weighting policies produce different candidates.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 378](../10-native-ai/378-derive-fedavg-from-a-shared-checkpoint.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** What is the difference between these two candidates, in scalar parameter units?

<details><summary>Reveal the full answer</summary>

1.040 − 1.029 = **0.011**. This difference is not itself a performance metric.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
