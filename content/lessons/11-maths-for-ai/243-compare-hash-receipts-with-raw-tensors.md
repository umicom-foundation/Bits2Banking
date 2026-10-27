# Mathematics for AI — Unit 243: Compare on-chain commitments with model tensors

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **compare on-chain commitments with model tensors**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

A SHA-256 digest occupies 32 bytes. Consider a 32 MiB dense parameter update (33,554,432 bytes).

## Full worked solution

The size ratio is 33,554,432/32 = **1,048,576**. Committing only a hash uses much less payload, but it does not put the corresponding tensor data on-chain or prove its learning quality. Consensus metadata adds its own overhead.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 387](../10-native-ai/387-compare-audit-record-chains-and-blockchain-consensus.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** How many bytes are needed for 1,000 raw SHA-256 digests before transaction metadata?

<details><summary>Reveal the full answer</summary>

1,000×32 = **32,000 bytes** (not 32 KiB).

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
