# Mathematics for AI — Unit 236: Count LoRA parameters and transfer bytes

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **count lora parameters and transfer bytes**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

A rank-8 adapter for a 4096×4096 dense projection has A shape 8×4096 and B shape 4096×8.

## Full worked solution

Scalars = 8×4096+4096×8 = **65,536**. At 2 bytes each this is **131,072 bytes = 128 KiB** (not counting protocol overhead, optimiser states or other layers).

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 383](../10-native-ai/383-aggregate-lora-updates-not-independent-factors.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** What is the payload for the same adapter in 4-byte FP32?

<details><summary>Reveal the full answer</summary>

65,536×4 = **262,144 bytes = 256 KiB**.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
