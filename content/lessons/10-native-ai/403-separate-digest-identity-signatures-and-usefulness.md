# Lesson 403 — Separate hash identity, signatures, execution and usefulness

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 252.

## Learning outcomes

Explain **separate hash identity, signatures, execution and usefulness**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

Four questions require four kinds of evidence: *Which bytes?* (content hash); *Who asserted this?* (signature under a trusted-key policy); *Was the computation performed?* (replay, attestation or a specific proof); and *Did the change improve the model?* (independent held-out evaluation). None is automatically implied by another. Build a receipt schema with a precise scope, verified by existing Framework cryptography rather than adding a second SHA-256 implementation.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Suppose worker A signs a statement committing to update hash U and base hash B. A correct signature proves that the holder of the signing key signed those bytes under the key trust assumptions. It does not prove the delta was created using the claimed GPU, that the dataset was licensed, or that final loss decreased.

## What can go wrong?

Promoting any signed claim directly into an approved checkpoint confuses authentication with scientific evidence.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Framework trust receipts, existing SHA-256/Ed25519 facilities and Helix approval are distinct reusable services.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Name the four evidence layers that must stay distinguishable.

<details><summary>Reveal the worked answer</summary>
<p>Byte identity, authenticated origin/authorisation, execution compliance and independent model usefulness.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 252](../11-maths-for-ai/252-compute-probability-of-random-challenge-detection.md) provides a quantitative counterpart.

## Primary reading

- [Gensyn OPEN-1B public audit and replay project](https://open1b.gensyn.ai/)
- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)

## Continue

[402 — previous lesson](402-test-poisoning-and-abnormal-norms.md) · [404 — next lesson](404-compare-record-chain-and-consensus-guarantees.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
