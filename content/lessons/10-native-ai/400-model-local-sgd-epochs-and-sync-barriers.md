# Lesson 400 — Model local SGD steps and synchronisation barriers

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 249.

## Learning outcomes

Explain **model local sgd steps and synchronisation barriers**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

Local SGD lets workers perform several optimisation steps between communications. DiLoCo-style systems reduce synchronisation frequency, but local models drift while workers see different data. A clean first experiment fixes the base model, local-step count, optimiser, token budget and synchronisation cadence. End-of-round weight deltas are combined by a documented outer rule, and the **entire new checkpoint** must be independently evaluated.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

If four workers each execute 200 steps with 1,024 training tokens per step, aggregate token work is 4×200×1,024 = 819,200 tokens per round. A central control receiving four 64 KiB deltas gets 256 KiB of payload, excluding networking overhead. Neither value measures validation improvement.

## What can go wrong?

An aggressive 200-step schedule might save bandwidth while increasing client drift. Reporting bytes alone conceals convergence failures.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

A future Umicom worker execution service can reuse checkpoint/optimiser primitives without embedding a scripting runtime.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What comparisons isolate communication cadence from total model work?

<details><summary>Reveal the worked answer</summary>
<p>Hold aggregate tokens, model, data and optimiser settings fixed while varying local steps per synchronisation and measuring held-out quality versus time and bytes.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 249](../11-maths-for-ai/249-model-wan-transfer-serialization-and-rtt.md) provides a quantitative counterpart.

## Primary reading

- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)
- [GeoMesh — Workload-Balanced and Sign-Compressed Geo-Distributed LLM Training (2026)](https://aclanthology.org/2026.findings-emnlp.720/)

## Continue

[399 — previous lesson](399-cancel-pending-jobs-without-changing-model-weights.md) · [401 — next lesson](401-quantify-non-iid-client-drift.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
