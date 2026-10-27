# Mathematics for AI — Unit 237: Calculate dense versus LoRA communication

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **calculate dense versus lora communication**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Compare a 4096×4096 dense matrix to a rank-8 adapter, both represented at 2 bytes per scalar.

## Full worked solution

Dense matrix: 4096² ×2 = **33,554,432 bytes = 32 MiB**. LoRA factors: 131,072 bytes = **0.125 MiB**. Ratio = 33,554,432/131,072 = **256**. This is a *single-projection payload ratio*, not a whole-model training acceleration.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 381](../10-native-ai/381-compare-local-sgd-diloco-and-sync-cadence.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** If the dense update requires 4-byte floats while the factors use 2 bytes, what is the payload ratio?

<details><summary>Reveal the full answer</summary>

(4096²×4)/131,072 = **512**. Check numerical fidelity when comparing different formats.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
