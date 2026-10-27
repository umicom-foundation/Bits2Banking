# Lesson 395 — Bind dataset commitments to independent usage permissions

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 247.

## Learning outcomes

Explain **bind dataset commitments to independent usage permissions**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A dataset commitment identifies bytes; a data-use policy determines whether those bytes may lawfully participate in training. **Identity and permission are different tests.** A SHA-256 value can match perfectly even when a finance document is not licensed for training. Training needs a reviewed manifest including source, retention, consent or appropriate legal basis, authorised objective and permitted sharing boundaries. Neither the worker’s assertion nor the existence of a public URL supplies that review.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

A worker requests shard digest S and policy digest P. The job expects P and records S. Admission can check digest equality, but only an independent dataset registry can establish that S is an approved shard under P. An unauthorised S must be rejected before it reaches the trainer.

## What can go wrong?

Publishing raw patient records, customer transactions, trade identifiers or proprietary documents in a shared research package is unacceptable simply because the source has a digest.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

RAG and banking applications can reuse the Framework source registry while keeping protected corpora at their originating institutions.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What additional evidence is required beyond a matching data hash?

<details><summary>Reveal the worked answer</summary>
<p>Reviewed rights and use permissions, provenance, data minimisation, partition/retention policy and an auditable authorisation decision.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 247](../11-maths-for-ai/247-avoid-size-overflow-in-admission-accounts.md) provides a quantitative counterpart.

## Primary reading

- [DataComp-LM: Designing a Benchmark for Language Model Data](https://arxiv.org/abs/2406.11794)

## Continue

[394 — previous lesson](394-admit-workers-through-scoped-tickets.md) · [396 — next lesson](396-reserve-claimed-transfer-bytes-before-admission.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
