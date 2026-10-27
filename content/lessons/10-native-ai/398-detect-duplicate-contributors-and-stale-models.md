# Lesson 398 — Reject duplicate contributors and mismatched base checkpoints

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 250.

## Learning outcomes

Explain **reject duplicate contributors and mismatched base checkpoints**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

Duplicate identity admission is a distinct condition from an already-completed ticket. A worker may send the same result twice after losing its acknowledgement; repeating it must not double its weight. A stale-base update is different: it may be a genuine update trained against yesterday’s parameters, but adding it to today’s model without a declared staleness rule changes the optimisation contract.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Worker A is admitted with 60 samples, delta +0.4 and base digest A. It retries that same result after acknowledgement. Counting it twice would inflate the total from 60 to 120 samples. A byte-identical retry is a delivery fact, not a second 60-sample training contribution.

## What can go wrong?

Signatures alone do not stop replay. A valid older signature can be replayed unless the round identifier, unique worker/update ID and checkpoint ancestry are bound to policy.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Data Server’s idempotency and durable inbox/outbox facilities should be investigated before building remote delivery.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** How should a coordinator respond to the same worker submitting a second update within one single-update round?

<details><summary>Reveal the worked answer</summary>
<p>Reject or idempotently return the original result without increasing accepted sample counts. A multi-update design needs a separately specified sequence policy.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 250](../11-maths-for-ai/250-compare-constant-and-staleness-decayed-weights.md) provides a quantitative counterpart.

## Primary reading

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)
- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)

## Continue

[397 — previous lesson](397-compose-admission-with-the-existing-fedavg-owner.md) · [399 — next lesson](399-cancel-pending-jobs-without-changing-model-weights.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
