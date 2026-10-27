# AI Research Frontiers — Lesson 009: Study federated LoRA beyond naive factor averaging

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

The optimisation object is a model update in **weight space**, not the individual A/B factor coordinates. Two different factorisations can encode the same delta; naive averaging destroys invariance. Variable-rank clients make the representation problem harder. A candidate protocol may aggregate reconstructed deltas, concatenate rank factors or compress the result to a selected rank with an explicit approximation budget.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

Independent baseline: sample-weighted full delta aggregation. Compare with factor averaging on the scalar A1=B1=1, A2=B2=−1 case; the correct delta average is 1 whereas factor average yields 0. Extend to random matrices with testable Frobenius error.

## Falsifiable hypothesis and measurements

Hypothesis: controlled rank-aware compression reduces transmitted bytes at a fixed non-inferiority bound on held-out loss. Retune all methods under matched update-communication and compute budgets, and report failed configurations.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [LoRA — Low-Rank Adaptation, Hu et al.](https://arxiv.org/abs/2106.09685)
- [Federated Low-Rank Adaptation for Foundation Models: A Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)
- [SDFLoRA — Selective Decoupled Federated LoRA (IJCAI 2026)](https://ijcai.org/proceedings/2026/533)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
