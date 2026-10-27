# AI Research Frontiers — Lesson 015: Govern independent held-out evaluation and data approval

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

A worker can optimise its own shard loss while degrading global performance. Separate local training data, held-out test data, and source permission evidence. Use predeclared metrics, repeated seeds and a quality non-inferiority threshold to decide whether an aggregate update may become a new model candidate. Helix approval can govern release, but the research workflow must not claim automatic proof from signed receipts.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

Evaluate finance and code domains separately. If finance loss improves by 0.03 while code loss deteriorates by 0.08, a single composite score may hide the regression. Keep both outcomes, compute variance across seeds and report the reviewer decision independently.

## Falsifiable hypothesis and measurements

Hypothesis: per-domain admission gates detect regressions that an aggregate-only threshold misses, at a measurable cost in accepted candidate rate.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [DataComp-LM: Designing a Benchmark for Language Model Data](https://arxiv.org/abs/2406.11794)
- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
