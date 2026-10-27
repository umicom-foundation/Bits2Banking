# AI Research Frontiers — Lesson 014: Investigate sparse experts over unreliable wide-area networks

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

MoE activates only a subset of experts for each token, but expert routing can require many cross-device dispatches. On a slow wide-area network, the inter-expert communication path may dominate. A decentralized MoE experiment should separate *model* sparsity from *network* transfer and include failure handling for missing experts. Contrast with state-space mixers whose recurrence changes memory/communication patterns.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

Suppose an expert dispatch transfers 8 KiB each direction for 100 tokens: 1.6 MiB of round-trip payload before metadata. At 10 Mbps, serialization alone exceeds one second; add RTT and the cost can dominate a small model. This is an illustrative bound, not measured MoE latency.

## Falsifiable hypothesis and measurements

Hypothesis: local expert placement with bounded fallback reduces WAN bytes per successfully processed token compared with naive round-robin expert placement while retaining a quality threshold.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [Attention Is All You Need](https://arxiv.org/abs/1706.03762)
- [Mamba: Linear-Time Sequence Modeling with Selective State Spaces](https://arxiv.org/abs/2312.00752)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
