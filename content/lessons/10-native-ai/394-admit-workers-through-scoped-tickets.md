# Lesson 394 — Admit workers using bounded process-local tickets

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 246.

## Learning outcomes

Explain **admit workers using bounded process-local tickets**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A ticket identifies one admitted worker assignment inside a single owner-managed job. Its fields may encode job identity, slot index and a serial value. The ticket is a **local lifetime guard**, not a digital signature or an Internet authentication token. It should be accepted once, refused after completion or cancellation, and never used as permission to access a data shard that was not separately authorised.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Job 42 admits worker A into slot 0 with serial 1. After A finishes, replaying ticket (42,1,0) must be rejected. A fabricated ticket with the wrong serial must also fail without changing pending assignment counts or memory reservations.

## What can go wrong?

Recycling an old ticket can corrupt a different worker’s reservation. Giving a ticket the same privilege as a signed identity creates an authorisation bypass.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Studio can inspect ticket state but should never expose it as a remotely trusted bearer secret.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Why does a generation counter not authenticate a remote worker?

<details><summary>Reveal the worked answer</summary>
<p>It proves only consistency with process-local state, not possession of an authorised cryptographic key or transport session.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 246](../11-maths-for-ai/246-calculate-two-parameter-sample-weighted-fedavg.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue

[393 — previous lesson](393-design-round-scoped-learning-jobs.md) · [395 — next lesson](395-bind-dataset-permissions-to-each-shard.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
