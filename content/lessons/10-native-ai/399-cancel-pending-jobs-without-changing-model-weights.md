# Lesson 399 — Cancel or time out pending jobs without creating gradients

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 248.

## Learning outcomes

Explain **cancel or time out pending jobs without creating gradients**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A cancelled assignment frees its **forecast byte reservation** and makes its ticket unusable. It does not create a zero-valued gradient, and it does not imply that the model should be updated from an incomplete sample of the intended worker population. Depending on round policy, the coordinator may wait, retry, reduce expected participation or abort. Each choice changes selection bias and time-to-target.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Assume four assigned workers but only A, B and C complete. D is cancelled. A mean of three valid updates is mathematically defined, but its relationship to a planned four-worker experiment is a *scientific* question. Report 3/4 participation and actual sample totals rather than calling it full completion.

## What can go wrong?

If a timeout is treated as a zero update with a positive sample count, the mean is diluted and the algorithm silently changes. A completed assignment that gets cancelled twice must not release its byte reservation twice.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Standalone Umicom LLM can expose a cancellation button that invokes one Framework lifecycle API rather than modifying model state itself.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Is a cancelled worker equivalent to a completed worker with a zero delta?

<details><summary>Reveal the worked answer</summary>
<p>No. The first contributes no samples; the second contributes a defined zero delta with a declared sample weight. Their denominators differ.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 248](../11-maths-for-ai/248-account-for-cancelled-workers-without-zero-deltas.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [GeoMesh — Workload-Balanced and Sign-Compressed Geo-Distributed LLM Training (2026)](https://aclanthology.org/2026.findings-emnlp.720/)

## Continue

[398 — previous lesson](398-detect-duplicate-contributors-and-stale-models.md) · [400 — next lesson](400-model-local-sgd-epochs-and-sync-barriers.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
