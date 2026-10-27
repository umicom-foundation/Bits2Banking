# AI Research Frontiers — Lesson 010: Compare heterogeneous training with GeoMesh and DiLoCo

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

Geographical training adds variable RTT, uplink bandwidth, local compute time and worker dropout. DiLoCo reduces synchronisation frequency; GeoMesh studies workload balancing and sign-compressed communication. These are substantive baselines, not unexplored techniques. A new scheduler needs an objective such as time-to-target quality or joules per useful improvement.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

Construct a 2×2 scenario: two workers (fast/slow), RTT 10/150 ms, local steps 10/100. Compare total token work and transmitted bytes while holding final quality target fixed. Include a centralised reference to identify distributed overhead.

## Falsifiable hypothesis and measurements

Hypothesis: a capacity-aware native scheduling policy improves time-to-target in a preregistered heterogeneous regime without worsening loss by more than a stated tolerance.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)
- [GeoMesh — Workload-Balanced and Sign-Compressed Geo-Distributed LLM Training (2026)](https://aclanthology.org/2026.findings-emnlp.720/)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
