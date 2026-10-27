# Mathematics for AI — Unit 244: Evaluate time-to-target and verification cost

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **evaluate time-to-target and verification cost**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

System A reaches a fixed held-out target in 1,000 s of training and 100 s of verification. System B takes 900 s of training and 300 s of verification.

## Full worked solution

End-to-end A = **1,100 s**; B = **1,200 s**. B has faster training but slower time-to-target when verification is required. Separately measure bytes, joules, security and quality.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 391](../10-native-ai/391-build-a-falsifiable-low-bandwidth-training-experiment.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** If B reduces its verification to 150 s without changing training time, which has lower total time and by how much?

<details><summary>Reveal the full answer</summary>

B becomes 900+150=**1,050 s**, so B is 50 s faster than A under these simplifying assumptions.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
