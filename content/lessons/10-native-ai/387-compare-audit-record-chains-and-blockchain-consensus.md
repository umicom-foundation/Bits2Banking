# Lesson 387 — Compare append-only receipts with blockchain consensus

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Level:** Intermediate and advanced research · **Implementation:** C23 / Assembly where qualified

## Learning objectives

By completing this lesson you will explain **compare append-only receipts with blockchain consensus**, distinguish established research from a proposed Umicom capability, and design a numerical or systems test with a falsifiable outcome.

## Concept and essential distinctions

An append-only record chain can link records by hashes. A distributed blockchain adds a consensus protocol among independent administrators, including assumptions about finality, membership and adversarial behaviour. A hash-linked file by itself is **not** a blockchain.

This lesson treats three separate boundaries as non-interchangeable: the *learning objective* that determines model quality, the *distributed systems protocol* that moves updates and controls work, and the *verification policy* that decides what evidence is trusted. A claimed training contribution is not promoted into an accepted checkpoint merely because it is well formed.

## Step-by-step worked example

Imagine three institutions approve a training result. One signed audit log managed by a trusted coordinator records “checkpoint X was evaluated and approved” cheaply. If none of the institutions trusts one administrator, a permissioned multi-party ledger may add useful governance; it also adds replication, agreement and operational overhead. Model tensors and private training batches should remain off-chain.

Check the example by writing down its inputs, units, initial model state, communication assumptions and expected output. Then vary exactly one input and predict the direction of change. In a full experiment, retain the complete reproducible configuration rather than reporting only an attractive final metric.

## What can go wrong?

A ledger should typically store bounded job/checkpoint commitments and approval receipts, never sensitive finance data or raw gradients. Timestamped commitments do not assert training legality, accuracy or compute correctness.

For any proposed optimiser or security improvement, retain a simple controlled baseline. A negative result is still a meaningful research observation when measured under declared conditions.

## Native C23 engineering connection

The Framework remains the authority for model mathematics, checkpoints, messaging and validation. The opt-in `UmiAiTrainingFederatedRound` component delivered with this course accepts compatible **weight-space deltas**, performs bounded sample-weighted accumulation and rejects malformed/duplicate contributions. It is **not** a remote trainer, privacy protocol, cryptographic verifier or blockchain. The `labs/native/distributed-learning/fedavg-round` program exercises the actual Framework API rather than copying the aggregator into the educational application.

A completed advanced implementation would connect locally trained deltas, verified identities, authorised datasets and held-out evaluation through the existing Framework services. New public release claims require independent qualification and not just a passing demonstration.

## Research method and suggested experiment

1. State one hypothesis that could be disproved and identify the exact baseline.
2. Pin one model/checkpoint identity, one reviewed dataset partition and an explicit seed.
3. Define what is observed: loss, bytes, elapsed time, memory, energy or verification rejection counts.
4. Try a success case and at least one deliberately malformed or harmful input.
5. Record the distinction between *observed*, *simulated* and *not tested* results.

## Exercise

**Question:** What concrete trust question should be answered before adopting a blockchain?

<details><summary>Reveal the worked answer</summary>

Which independently governed parties must agree on an ordering/outcome without trusting a single log administrator, and why would signed receipts be insufficient?

</details>

## Mathematics companion

[Related Maths for AI Unit 240](../11-maths-for-ai/240-calculate-l2-norm-and-clipping-scale.md). Consult the mathematics track for dimension, ratio, security-cost and numerical-error calculations.

## Verified research starting points

- [SoK: Decentralized AI (DeAI) (2024 preprint)](https://arxiv.org/abs/2411.17461)
- [Proof of Learning (PoLe) — Lan et al. (2020)](https://arxiv.org/abs/2007.15145)
- [Proof-of-Learning with Incentive Security (2024 preprint)](https://arxiv.org/abs/2404.09005)

## Continue learning

[Editable curriculum learning path](../../courses/llm-from-scratch/distributed-ai-research-learning-path.html) · [Introductory distributed-learning course](../../courses/distributed-learning/index.html)

*Service to Many Leads to Greatness.*
