# Lesson 407 — Design LAN/WAN experiments with reproducible synthetic data

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 249.

## Learning outcomes

Explain **design lan/wan experiments with reproducible synthetic data**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A single-machine simulator proves state-machine logic, not real wide-area communication. A trustworthy next phase uses two independently running native workers over a controlled LAN, then a documented WAN profile with latency, bandwidth limits, dropout and hardware variability. Reuse Framework messaging, job leases and source identity; do not implement a parallel application-local transport protocol.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

For a 64 KiB update over a 10 Mbps ideal link, payload-only serialization takes (65,536×8)/10,000,000 ≈52.43 ms. With 100 ms round-trip latency and one request/response, a generous lower bound is roughly 152 ms before TLS, retransmissions, payload framing and computation. Call this a *modelled lower bound*, not measured network time.

## What can go wrong?

A perfect in-process test cannot prove cancellation recovery after a network partition. A simulation of 250 ms RTT must be labelled simulated.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom OS and native Studio can visualise worker diagnostics, but the Framework remains the authority for job state and network policy.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What evidence differentiates a real distributed result from a local simulation?

<details><summary>Reveal the worked answer</summary>
<p>Independent processes/hosts, recorded route/network conditions, transport counters, logs, actual end-to-end timing and reproducible checkpoint identities.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 249](../11-maths-for-ai/249-model-wan-transfer-serialization-and-rtt.md) provides a quantitative counterpart.

## Primary reading

- [GeoMesh — Workload-Balanced and Sign-Compressed Geo-Distributed LLM Training (2026)](https://aclanthology.org/2026.findings-emnlp.720/)
- [DiLoCo — Distributed Low-Communication Training](https://arxiv.org/abs/2311.08105)

## Continue

[406 — previous lesson](406-compare-fedavg-and-federated-lora-deltas.md) · [408 — next lesson](408-capstone-qualify-a-three-worker-native-learning-round.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
