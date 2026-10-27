# Lesson 405 — Evaluate random training verification and replay economics

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 252.

## Learning outcomes

Explain **evaluate random training verification and replay economics**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A random challenge audits only a fraction of claimed worker steps. If an adversary corrupts a known fraction of independent steps and auditors sample uniformly, detection probability can be estimated; correlated cheating, adaptive adversaries and nondeterministic GPU behaviour break naive assumptions. Verification must declare its exact claim, false rejection rate, cost and challenge selection policy.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

A worker has 100 steps, and 10% are fraudulent. If five independent challenges each hit a uniformly random step with replacement, P(detect at least one)=1−0.9^5≈40.951%. At a per-challenge verification cost of 0.1 GPU-seconds, total audit costs 0.5 GPU-seconds; full re-execution may cost much more. This does not certify the remaining 95 steps.

## What can go wrong?

If the worker can predict challenge positions, it may cheat only outside them. Hidden data or protected gradients may prevent exact replay and require a different protocol.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

The research can build audit evidence into Framework while leaving payout and ledger decisions optional.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Does passing five challenges prove every local training step was honest?

<details><summary>Reveal the worked answer</summary>
<p>No. It is limited evidence under the challenge-selection, adversary and numerical reproducibility assumptions.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 252](../11-maths-for-ai/252-compute-probability-of-random-challenge-detection.md) provides a quantitative counterpart.

## Primary reading

- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)
- [INTELLECT-2 — Globally Decentralized Reinforcement Learning](https://arxiv.org/abs/2505.07291)

## Continue

[404 — previous lesson](404-compare-record-chain-and-consensus-guarantees.md) · [406 — next lesson](406-compare-fedavg-and-federated-lora-deltas.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
