# Lesson 401 — Measure non-IID client drift before choosing an aggregation rule

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 255.

## Learning outcomes

Explain **measure non-iid client drift before choosing an aggregation rule**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

When each worker sees a different domain or class distribution, equally valid local updates may point in conflicting directions. This is not a network bug. Non-IID partitions can alter convergence, fairness and catastrophic forgetting. A reproducible study must preserve the partition identity, class mixture, local steps, held-out global test and per-domain evaluation, then compare FedAvg against at least one local-only or central control.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Worker A sees 90% finance and 10% code examples; B sees 10% finance and 90% code. An aggregate 50/50 domain distribution does not mean either worker sees IID data. Under more local steps, their parameter trajectories may diverge. Report both global loss and finance/code loss.

## What can go wrong?

A single combined metric can hide a domain regression. Publishing only the better client’s outcome selects evidence after the fact.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

This applies to Umicom’s education, banking and developer assistants, which have different authorised domain corpora.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** Why can a statistically correct weighted average still reduce quality on one domain?

<details><summary>Reveal the worked answer</summary>
<p>It optimises a mixture of heterogeneous objectives; improvement on the weighted mixture does not guarantee improvement for every client/domain.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 255](../11-maths-for-ai/255-quantify-domain-skew-between-two-workers.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Federated Low-Rank Adaptation for Foundation Models: A Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)

## Continue

[400 — previous lesson](400-model-local-sgd-epochs-and-sync-barriers.md) · [402 — next lesson](402-test-poisoning-and-abnormal-norms.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
