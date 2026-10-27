# Lesson 396 — Reserve declared transfer bytes under a finite budget

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 248.

## Learning outcomes

Explain **reserve declared transfer bytes under a finite budget**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A coordinator may reserve *expected* update transport bytes while a worker is pending. Such reservations control over-admission, but are not measurements of bytes actually transferred. They are released after completion or cancellation. Design two ledgers: **declared outstanding reservations** and **observed transport counters**, and never label the first one as throughput.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Budget: 96 KiB. Assignment A requests 50 KiB and is admitted. B requests 50 KiB and must wait because 100 KiB exceeds 96 KiB. After A finishes, B can be admitted. The peak declared reservation remains 50 KiB, while the total across time may be 100 KiB.

## What can go wrong?

A cumulative counter confused with a concurrent reservation creates unnecessary rejection. An unbounded sum of user-provided sizes can overflow a size_t without checked addition.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Framework admission can later consume the existing network quota and messaging primitives; no standalone Python scheduler is required.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Does releasing a reservation imply that a network transfer really happened?

<details><summary>Reveal the worked answer</summary>
<p>No. Reservation is admission accounting. Actual transport requires independent byte counters and delivery acknowledgements.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 248](../11-maths-for-ai/248-account-for-cancelled-workers-without-zero-deltas.md) provides a quantitative counterpart.

## Primary reading

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)
- [GeoMesh — Workload-Balanced and Sign-Compressed Geo-Distributed LLM Training (2026)](https://aclanthology.org/2026.findings-emnlp.720/)

## Continue

[395 — previous lesson](395-bind-dataset-permissions-to-each-shard.md) · [397 — next lesson](397-compose-admission-with-the-existing-fedavg-owner.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
