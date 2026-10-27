# Mathematics for AI — Unit 239: Compute WAN transfer and RTT lower bounds

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Integer arithmetic, proportions and earlier Maths for AI units.

## Learning outcome

Use explicit dimensions, units and algebra to **compute wan transfer and rtt lower bounds**. Distinguish an identity, estimate, simulation and an empirically measured result.

## Starting assumptions

Assume a 128 KiB update, effective uplink throughput 10 Mbps, and one 150 ms RTT. Ignore protocol/compute overhead.

## Full worked solution

128 KiB = 131,072 bytes = 1,048,576 bits. Transfer duration = 1,048,576/10,000,000 = **0.1048576 s**. Add 0.150 s RTT to obtain **0.2548576 s** illustrative lower-bound path time.

The calculation is exact where no approximation mark appears. Capacity and communication examples exclude allocator overhead, transport headers, retry traffic, encryption padding, optimiser states and replication unless explicitly noted. None of these numerical examples proves model quality.

## Check the units

Record whether the result is a scalar parameter, weight-space delta, byte count, probability, millisecond, percentage or ratio. In scientific measurements, record both the numerator and denominator rather than only the displayed comparison.

## Connect to the research course

[LLM Lesson 381](../10-native-ai/381-compare-local-sgd-diloco-and-sync-cadence.md) applies the calculation to one concrete native inference or distributed-learning problem.

## Exercise

**Question:** With 100 Mbps effective uplink and the same RTT, what is the idealised total?

<details><summary>Reveal the full answer</summary>

0.01048576+0.150 = **0.16048576 s**. RTT now dominates.

</details>

## Further exploration

Change exactly one assumption, recompute the expression and say whether it changes an engineering decision. Report measurement uncertainty only for observed data, not for an algebraic identity.

## Continue learning

[Mathematics learning path](../../courses/maths-for-ai/distributed-ai-mathematics.html) · [Introductory distributed learning](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
