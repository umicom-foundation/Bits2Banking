# Lesson 404 — Compare tamper-evident records with blockchain consensus

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 253.

## Learning outcomes

Explain **compare tamper-evident records with blockchain consensus**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

An append-only hash chain links records so later alterations become detectable when the trusted head is known. That is useful for local training provenance. A blockchain adds an agreement protocol across independent parties, with assumptions about membership, faults, finality, upgrades and dispute resolution. A chain of hashes without network agreement is not a distributed consensus system.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Three records contain hashes H1=SHA256(R1), H2=SHA256(H1||R2), H3=SHA256(H2||R3). Changing R1 changes subsequent commitments. This statement assumes canonical serialisation and access to an independently trusted final head; it says nothing about honest original inputs.

## What can go wrong?

Publishing private gradients or customer identifiers on a public ledger creates confidentiality and deletion hazards. Large model artefacts should be stored off-chain with access controls.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Umicom Financial Platform and Umicoin can eventually consume approved receipts, but neither should sit in a native gradient hot path.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** When is a blockchain more defensible than a signed append-only store?

<details><summary>Reveal the worked answer</summary>
<p>When independent administrative parties genuinely need shared ordering/finality and the incremental governance benefit justifies the new cost and threat assumptions.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 253](../11-maths-for-ai/253-compare-verification-gpu-seconds-to-training-cost.md) provides a quantitative counterpart.

## Primary reading

- [Bitcoin: A Peer-to-Peer Electronic Cash System](https://bitcoin.org/bitcoin.pdf)
- [Can Blockchains Reliably Train Machine Learning Models?](https://arxiv.org/abs/2307.07066)

## Continue

[403 — previous lesson](403-separate-digest-identity-signatures-and-usefulness.md) · [405 — next lesson](405-evaluate-verification-challenges-and-replay-cost.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
