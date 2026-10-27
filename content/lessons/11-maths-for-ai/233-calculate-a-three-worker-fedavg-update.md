# Mathematics for AI — Unit 233: Calculate a three-worker FedAvg update

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **calculate a three-worker fedavg update**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Let local update deltas be +0.050, −0.010, +0.080 with distinct sample counts 100, 250 and 150. The total is N=500.

## Full worked solution

Weighted numerator = 100×0.050 + 250×(−0.010) + 150×0.080 = 5 − 2.5 + 12 = 14.5. Dividing by 500 gives **0.029**. Starting at 1.000 gives **1.029**.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 377](../10-native-ai/377-separate-distributed-learning-from-inference-scheduling.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** If contributor B has twice as many samples while the others stay fixed, recompute the weighted update.

<details><summary>Reveal the full answer</summary>

The counts are 100, 500, 150 (N=750). Numerator = 5 − 5 + 12 = 12; update = 12/750 = **0.016**.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
