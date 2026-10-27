# Lesson 397 — Compose admission with the established FedAvg owner

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 246.

## Learning outcomes

Explain **compose admission with the established fedavg owner**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A reliable extension does not reimplement sample-weighted model arithmetic. The admission service verifies metadata, then delegates the complete FP32 vector to `UmiAiTrainingFederatedRoundSubmit`. The underlying round checks counts, duplicate contributors, finite values and norm limits. Only if this native operation succeeds does the coordinator close the ticket. This is a two-stage control boundary, **not proof of useful training**.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Three distinct sample counts 100, 250, 150 accompany delta values +0.05, −0.01, +0.08. The existing weighted arithmetic returns (100×0.05 + 250×(−0.01) + 150×0.08)/500 = +0.029. The job service accounts for admission and cancellation but does not calculate a second mean.

## What can go wrong?

If the job marks a worker complete before the aggregator accepts its float vector, failure leaves an acknowledged contribution that never reached the model. Conversely, accepting the vector twice biases the result.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Education can demonstrate a complete synthetic round using the same shared SDK that a future LLM worker would call.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Where should the multiplication by sample count occur?

<details><summary>Reveal the worked answer</summary>
<p>Inside the canonical Framework federated-round implementation, not in the job coordinator or an application wrapper.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 246](../11-maths-for-ai/246-calculate-two-parameter-sample-weighted-fedavg.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)

## Continue

[396 — previous lesson](396-reserve-claimed-transfer-bytes-before-admission.md) · [398 — next lesson](398-detect-duplicate-contributors-and-stale-models.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
