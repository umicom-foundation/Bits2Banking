# Mathematics for AI — Unit 238: Quantify non-IID client mixtures

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **quantify non-iid client mixtures**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Two equal-size institutions each have 100 examples. A has 90 coding and 10 finance; B has 10 coding and 90 finance.

## Full worked solution

Combined 200 examples contain 100 coding and 100 finance: 50% each. But each local distribution is strongly skewed. Equal aggregate counts do **not** mean their gradients or outcomes will agree.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 380](../10-native-ai/380-understand-non-iid-client-data-and-bias.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** If B contributes 300 examples at its original 10% coding ratio, what fraction of the combined 400 examples are coding?

<details><summary>Reveal the full answer</summary>

A contributes 90 coding. B contributes 30 coding. Total 120/400 = **30% coding**.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
