# Mathematics for AI — Unit 242: Separate aggregate totals from private components

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **separate aggregate totals from private components**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Three workers hold values 4, 7 and 9. Ordinary aggregation exposes all individual inputs to the coordinator.

## Full worked solution

Sum = 4+7+9 = **20**. A genuine secure-sum protocol might disclose only 20 under defined cryptographic/dropout assumptions. Merely adding classroom masks does not constitute such a protocol.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 385](../10-native-ai/385-secure-aggregation-versus-update-inspection.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** If only the sum 20 is revealed and the coordinator knows the first two values 4 and 7, is the third value hidden?

<details><summary>Reveal the full answer</summary>

No. It can infer 20−4−7=**9**. Aggregate release can still leak under background knowledge.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
