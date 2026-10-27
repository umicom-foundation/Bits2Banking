# Lesson 408 — Capstone: qualify a bounded three-worker learning round

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab  
**Implementation approach:** native C23, with Assembly only after justified profiling.  
**Prerequisites:** Lessons 377–392, Mathematics Unit 256.

## Learning outcomes

Explain **capstone: qualify a bounded three-worker learning round**, identify the exact boundary between evidence, model arithmetic and coordination, and design at least one test that can fail. Distinguish implemented Umicom source from suggested research.

## Concept and mechanism

A credible capstone composes the new job coordinator with the previously delivered numeric FedAvg round. It admits three authorised synthetic assignments against one immutable base label, reserves declared bytes, accepts finite and correctly shaped weight-space deltas, rejects a forged/stale ticket, and returns a *candidate* aggregated update. Separately demonstrate that the unchanged model is not automatically trained or released.

A correct research system starts with the immutable experiment contract: a common base checkpoint, authorised dataset partitions, an explicit sample-count rule, a deterministic round identifier and a preregistered evaluation metric. Distributed operation also requires stated concurrency, failure and network assumptions. The mathematical candidate resulting from averaging does not become an approved model checkpoint without an independent quality gate.

## Worked scenario

Set θ0=1.000. A supplies 100 examples and ΔA=+0.05, B 250 and ΔB=−0.01, C 150 and ΔC=+0.08. The native round returns Δ=0.029, so the **illustrative proposed** θ1=1.029. No real neural training, dataset validation, cross-process communication or quality improvement is implied by this arithmetic.

## What can go wrong?

A successful native CTest is an engineering result, not a published research result. The capstone must report the full Windows Framework integration and held-out model evaluation as *not performed* until evidenced.

## Native Umicom engineering connection

The Framework's established `UmiAiTrainingFederatedRound` is the sole numeric FedAvg-delta owner. The additive `UmiAiTrainingFederatedJob` admission component tracks one round of assignments and routes accepted full FP32 deltas through that existing numeric API. It does **not** train remote workers, sign contributions, verify dataset rights, provide Byzantine resilience, implement secure aggregation or run blockchain consensus. The remaining training, checkpoint, messaging and governance functions must be composed from reviewed Framework capabilities rather than duplicated in application code.

The learning laboratory can be used by Bits2Banking learners and later consumed by thin Umicom LLM/Studio interfaces.

## Verification exercise

Reproduce the worked case using synthetic inputs. Then reject an invalid, stale, mismatched or adversarial input without changing the accepted aggregate. Report the exact result and a separate list of work **not measured**: real network RTT, GPU hours, held-out model improvement and privacy guarantee.

**Question:** What conditions must hold before a candidate θ1 can be approved for deployment?

<details><summary>Reveal the worked answer</summary>
<p>Independently verified dataset and checkpoint provenance, consistent execution evidence, complete numerical tests, held-out quality/safety checks and the applicable human governance gate.</p>
</details>

## Mathematics connection

[Mathematics for AI — Unit 256](../11-maths-for-ai/256-compare-time-to-target-quality-vs-raw-throughput.md) provides a quantitative counterpart.

## Primary reading

- [Federated Averaging — McMahan et al., AISTATS 2017](https://proceedings.mlr.press/v54/mcmahan17a.html)
- [Proof of Learning (PoLe)](https://arxiv.org/abs/2007.15145)
- [Federated Low-Rank Adaptation for Foundation Models: A Survey (IJCAI 2025)](https://ijcai.org/proceedings/2025/1196)

## Continue

[407 — previous lesson](407-reproduce-lan-wan-training-with-authorised-fixtures.md) · [Distributed Learning continued](../12-distributed-learning/013-bind-one-worker-to-one-round.md) · [HTML study route](../../courses/llm-from-scratch/federated-job-learning-path.html) · [Introduction to Distributed Learning](../12-distributed-learning/013-bind-one-worker-to-one-round.md)

*Service to Many Leads to Greatness.*
