# Lesson 402 — Bound suspicious deltas and design a poisoning experiment

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 251.

## Learning outcomes

Explain **bound suspicious deltas and design a poisoning experiment**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A norm limit is a basic numerical safety gate: large or non-finite vectors may be rejected before accumulation. It does **not** guarantee Byzantine robustness. A malicious update of small norm can still be directionally harmful or implement a backdoor. Experiments should include random updates, sign flips, scaled updates and valid-but-harmful updates, each compared against an honest baseline.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Given delta=(3,4), its L2 norm is 5. Under a maximum norm 2.5, a reject-only policy refuses the vector. A separately specified clipping policy might scale it to (1.5,2.0). These are different algorithms and must not be silently interchanged.

## What can go wrong?

An acceptance count of 100% is not proof of honesty; it may simply mean the attacks fall inside a loose norm threshold.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

Use only synthetic training data for attack fixtures and keep privileged financial data outside shared test networks.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What distinguishes norm rejection from robust aggregation?

<details><summary>Reveal the worked answer</summary>
<p>Norm rejection tests magnitude/finite constraints; robust aggregation models adversarial participants and considers how even bounded malicious updates influence the resulting model.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 251](../11-maths-for-ai/251-calculate-delta-l2-norm-and-clipping.md) provides a quantitative counterpart.

## Primary reading

- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)
- [Practical Secure Aggregation — Bonawitz et al.](https://arxiv.org/abs/1611.04482)

## Continue

[401 — previous lesson](401-quantify-non-iid-client-drift.md) · [403 — next lesson](403-separate-digest-identity-signatures-and-usefulness.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
