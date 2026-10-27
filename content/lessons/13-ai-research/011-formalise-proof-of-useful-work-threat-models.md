# AI Research Frontiers — Lesson 011: Formalise proof-of-useful-learning threat models

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Level:** Advanced research · **Implementation focus:** C23/Assembly where justified.

## Research problem and state of practice

A receipt may commit to a job, base checkpoint, dataset hash and output update. This establishes a statement about bytes, not the fidelity of expensive neural optimisation. A verifier must choose between full replay, probabilistic challenges, statistical checks and hardware trust assumptions. The novelty lies in the trade-off among detection power, verification cost, private data constraints and adversarial adaptation.

This subject has established prior art. A promising idea becomes a research contribution only when it names a competing baseline, controls the evaluation budget, demonstrates a reproducible improvement or reports a valid negative result. Keep paper claims distinct from independently replicated observations.

## Worked research design

If corrupted-step fraction is 0.1 and five independent challenges are uniformly random with replacement, estimated detection chance is 40.951%. That is not a guarantee against an adaptive attacker. Compare against full replay and a no-verification control.

## Falsifiable hypothesis and measurements

Hypothesis: a bounded audit policy reduces accepted malicious contributions under a stated cost budget; measure both false acceptance and false rejection with independent attacks.

Collect an immutable dataset/checkpoint identifier, compiler/backend version, model shape, worker topology, bandwidth and RTT, random seeds, held-out evaluation, communication bytes, total time and verified cost. Pre-register the main success metric before comparing implementations; report confidence ranges if observed effects are small.

## Integration boundary

Use existing Framework training, optimisation, model-provenance, messaging and lifecycle APIs. Where a new capability is required, develop a bounded native C23 component and qualify it against a simple independent numerical oracle. Do not place unreviewed learner code directly in the production Bank/TMS services, and do not claim networked training or cryptographic proof from an in-process demonstration.

## Questions for a research notebook

1. Which property of the method is genuinely novel relative to the strongest listed baseline?
2. Which hardware, dataset or adversary assumption could reverse the outcome?
3. What failed experiment would disprove the proposed advantage?
4. How could a different research group reproduce every measured result?

## Primary literature

- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)
- [INTELLECT-2 — Globally Decentralized Reinforcement Learning](https://arxiv.org/abs/2505.07291)
- [Gensyn OPEN-1B public audit and replay project](https://open1b.gensyn.ai/)

[Advanced research route](../../courses/ai-research/federated-research-extensions.html) · [Distributed Learning course](../../courses/distributed-learning/rounds-and-verification.html)

*Service to Many Leads to Greatness.*
